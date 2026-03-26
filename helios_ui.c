/**
 * @file helios_ui.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "helios_ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    lv_obj_t * (*screen_fn)(void);   // function that returns screen object
    lv_scr_load_anim_t anim;         // animation to use
} gesture_action_t;

typedef struct {
    gesture_action_t left;
    gesture_action_t right;
    gesture_action_t up;
    gesture_action_t down;
} gesture_map_t;

typedef struct {
    lv_obj_t * obj;
    lv_obj_t * drag_obj;
    int32_t start_y;
    int32_t panel_y;
    int32_t height;
    bool drag;
    bool open;
} control_panel_t;

typedef lv_obj_t * (*settings_item_create_cb_t)(lv_obj_t * parent);

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void screen_res_cb(lv_event_t *e);
static void screen_gesture_event_cb(lv_event_t * e);
static void lv_obj_animate_y(lv_obj_t *obj, int32_t start, int32_t end, int32_t duration);
static void scroll_y_end_listener_cb(lv_event_t *e);
static void scroll_x_end_listener_cb(lv_event_t *e);

static void home_screen_event_cb(lv_event_t * e);
static void on_control_widget_cb(lv_event_t * e);
static void control_widget_cb(void * var, int32_t value);
static void on_control_drag_cb(lv_event_t * e);

static void panel_events_cb(lv_event_code_t code);

static lv_obj_t * get_list_from_wd(lv_obj_t * parent, const char * name);

static void settings_item_helper(lv_obj_t * parent, const void * icon,  const char * name, settings_item_create_cb_t function);

/**********************
 *  STATIC VARIABLES
 **********************/
static control_panel_t control_widget_home;

static bool notifications_to_apps = false;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void helios_ui_init(const char * asset_path)
{
    helios_ui_init_gen(asset_path);

    /* Add your own custom code here if needed */
#if defined(LV_EDITOR_PREVIEW)
    lv_display_t *disp = lv_display_get_default();
    if (disp) {
        lv_display_add_event_cb(disp, screen_res_cb, LV_EVENT_RESOLUTION_CHANGED, NULL);
        lv_display_send_event(disp, LV_EVENT_RESOLUTION_CHANGED, NULL);
    }
#endif

}

lv_obj_t * screen_home(void)
{
    lv_obj_t * home = home_create();

    static gesture_map_t gestures = {
        .left  = { screen_applications, LV_SCR_LOAD_ANIM_OVER_LEFT },
        .right = { screen_notifications, LV_SCR_LOAD_ANIM_OVER_RIGHT },
        .up    = { screen_widgets, LV_SCR_LOAD_ANIM_OVER_TOP },
        .down  = { NULL, 0 },
    };

    lv_obj_add_event_cb(home, screen_gesture_event_cb, LV_EVENT_GESTURE, &gestures);

    control_widget_home.obj = control_panel_create(home);

    control_widget_home.drag_obj = lv_obj_find_by_name(control_widget_home.obj, "drag_control");
    if (control_widget_home.drag_obj) {
        lv_obj_add_event_cb(control_widget_home.drag_obj, on_control_drag_cb, LV_EVENT_ALL, home);
    }

    // lv_obj_t * list = get_list_from_wd(control_widget_home.obj, "control_list");
    // if (list) {
    //     lv_obj_set_flag(list, LV_OBJ_FLAG_EVENT_BUBBLE, false);
    // }

    static int scroll_pos = 0;
    lv_obj_t * list = get_list_from_wd(control_widget_home.obj, "control_list");
    if (list) {
        lv_obj_scroll_to_y(list, scroll_pos, LV_ANIM_OFF);
        lv_obj_add_event_cb(list, scroll_y_end_listener_cb, LV_EVENT_SCROLL_END, &scroll_pos);
        lv_obj_set_flag(list, LV_OBJ_FLAG_EVENT_BUBBLE, false);
    }

    lv_obj_set_align(control_widget_home.obj, LV_ALIGN_TOP_MID);
    // lv_obj_add_event_cb(control_widget_home.obj, on_control_widget_cb, LV_EVENT_ALL, NULL);

    // lv_area_t cont_a;
    // lv_obj_get_coords(control_widget_home.obj, &cont_a);
    // control_widget_home.height = lv_area_get_height(&cont_a);

    control_widget_home.height = lv_obj_get_height(home);
    // LV_LOG_USER("Control height %d", control_widget_home.height);
    lv_obj_set_y(control_widget_home.obj, -control_widget_home.height);

    lv_obj_add_event_cb(home, home_screen_event_cb, LV_EVENT_ALL, NULL);

    return home;

}


lv_obj_t * screen_applications(void)
{

    lv_obj_t * apps = applications_create();

    static gesture_map_t gestures = {
        .left  = { NULL, 0 },
        .right = { screen_home, LV_SCR_LOAD_ANIM_OUT_RIGHT },
        .up    = { NULL, 0 },
        .down  = { NULL, 0 },
    };

    lv_obj_add_event_cb(apps, screen_gesture_event_cb, LV_EVENT_GESTURE, &gestures);

    static int scroll_pos = 0;
    lv_obj_t * app_list = get_list_from_wd(apps, "app_list");
    if (app_list) {
        lv_obj_scroll_to_y(app_list, 1, LV_ANIM_OFF); /* Circular scroll trigger fix */
        lv_obj_scroll_to_y(app_list, scroll_pos, LV_ANIM_OFF);
        lv_obj_add_event_cb(app_list, scroll_y_end_listener_cb, LV_EVENT_SCROLL_END, &scroll_pos);
    }

    return apps;
}

lv_obj_t * screen_notifications(void)
{

    lv_obj_t * notifications = notifications_create();

    static gesture_map_t gestures = {
        .left  = { screen_home, LV_SCR_LOAD_ANIM_OUT_LEFT },
        .right = { NULL, 0 },
        .up    = { NULL, 0 },
        .down  = { NULL, 0 },
    };

    if (notifications_to_apps) {
        gesture_action_t apps = {
            .screen_fn = screen_applications, 
            .anim = LV_SCR_LOAD_ANIM_OUT_RIGHT
        };
        gestures.left.screen_fn = NULL;
        gestures.right = apps;
        notifications_to_apps = false;
    } else {
        gesture_action_t home = {
            .screen_fn = screen_home, 
            .anim = LV_SCR_LOAD_ANIM_OUT_LEFT
        };
        gestures.right.screen_fn = NULL;
        gestures.left = home;
    }

    lv_obj_add_event_cb(notifications, screen_gesture_event_cb, LV_EVENT_GESTURE, &gestures);

    static int scroll_pos = 0;
    lv_obj_t * list = get_list_from_wd(notifications, "notifications_list");
    if (list) {
        lv_obj_scroll_to_y(list, scroll_pos, LV_ANIM_OFF);
        lv_obj_add_event_cb(list, scroll_y_end_listener_cb, LV_EVENT_SCROLL_END, &scroll_pos);
    }

    return notifications;
}

lv_obj_t * screen_widgets(void)
{

    lv_obj_t * widgets = widgets_create();

    static gesture_map_t gestures = {
        .left  = { NULL, 0 },
        .right = { NULL, 0 },
        .up    = { NULL, 0 },
        .down  = { screen_home, LV_SCR_LOAD_ANIM_OUT_BOTTOM },
    };

    lv_obj_add_event_cb(widgets, screen_gesture_event_cb, LV_EVENT_GESTURE, &gestures);

    static int scroll_pos = 0;
    lv_obj_scroll_to_x(widgets, scroll_pos, LV_ANIM_OFF);
    lv_obj_add_event_cb(widgets, scroll_x_end_listener_cb, LV_EVENT_SCROLL_END, &scroll_pos);

    return widgets;
}

lv_obj_t * screen_settings(void)
{

    lv_obj_t * settings = settings_create();

    static gesture_map_t gestures = {
        .left  = { NULL, 0 },
        .right = { screen_applications, LV_SCR_LOAD_ANIM_OUT_RIGHT },
        .up    = { NULL, 0 },
        .down  = { NULL, 0 },
    };

    lv_obj_add_event_cb(settings, screen_gesture_event_cb, LV_EVENT_GESTURE, &gestures);

    static int scroll_pos = 0;
    lv_obj_t * list = get_list_from_wd(settings, "main_settings_list");
    if (list) {

        lv_obj_clean(list);

        settings_item_helper(list, icon_settings_monitor, "Display", settings_display_create);
        settings_item_helper(list, icon_settings_smartwatch, "System", settings_system_create);
        settings_item_helper(list, icon_settings_bell, "Alerts", settings_alert_create);
        settings_item_helper(list, icon_settings_power, "Battery", settings_battery_create);
        settings_item_helper(list, icon_settings_harddisk, "Storage", settings_storage_create);
        settings_item_helper(list, icon_settings_information, "About", settings_about_create);

        lv_obj_scroll_to_y(list, 1, LV_ANIM_OFF); /* Circular scroll trigger fix */
        lv_obj_scroll_to_y(list, scroll_pos, LV_ANIM_OFF);
        lv_obj_add_event_cb(list, scroll_y_end_listener_cb, LV_EVENT_SCROLL_END, &scroll_pos);
    }

    return settings;
}

lv_obj_t * screen_weather(void)
{

    lv_obj_t * weather = weather_create();

    static gesture_map_t gestures = {
        .left  = { NULL, 0 },
        .right = { screen_applications, LV_SCR_LOAD_ANIM_OUT_RIGHT },
        .up    = { NULL, 0 },
        .down  = { NULL, 0 },
    };

    lv_obj_add_event_cb(weather, screen_gesture_event_cb, LV_EVENT_GESTURE, &gestures);

    static int scroll_pos = 0;
    lv_obj_t * list = get_list_from_wd(weather, "weather_list");
    if (list) {

        lv_obj_scroll_to_y(list, scroll_pos, LV_ANIM_OFF);
        lv_obj_add_event_cb(list, scroll_y_end_listener_cb, LV_EVENT_SCROLL_END, &scroll_pos);
    }

    return weather;
}

int32_t get_screen_width(int32_t index)
{
    switch (index)
    {
        case 0: return 466;
        case 1: return 360;
        case 2: return 240;
    }
    return 466;

}

void on_settings_clicked_cb(lv_event_t * e)
{
    lv_screen_load_anim(screen_settings(), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}

void on_weather_clicked_cb(lv_event_t * e)
{
    lv_screen_load_anim(screen_weather(), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}

void on_notifications_clicked_cb(lv_event_t * e)
{
    notifications_to_apps = true;
    lv_screen_load_anim(screen_notifications(), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}


void on_simulator_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *screen = lv_event_get_target(e);

    if (code == LV_EVENT_SCREEN_LOADED) {

        lv_screen_load(screen_home());

    }
}

void set_screen(int32_t w, int32_t h)
{
    if (w >= 400) {
        lv_subject_set_int(&sb_screen_size, 0); // 466
    } else if (w >= 300) {
        lv_subject_set_int(&sb_screen_size, 1); // 360
    } else {
        lv_subject_set_int(&sb_screen_size, 2); // 240
    }
    lv_subject_set_int(&sb_screen_type, w == h ? 0 : 1);
}


/**********************
 *   STATIC FUNCTIONS
 **********************/
static void control_widget_cb(void * var, int32_t value)
{

    int32_t opa = lv_map(value, -control_widget_home.height, 0, 55, 255);
    lv_obj_set_y(var, value);
    lv_obj_set_style_bg_opa(var, opa, 0);

}

static void on_control_widget_cb(lv_event_t * e)
{
    lv_obj_t *cont = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_GESTURE) {
        LV_LOG_USER("Gesture detected");
    }

    // if (code == LV_EVENT_SCROLL_BEGIN) {
    //     lv_obj_set_flag(cont, LV_OBJ_FLAG_EVENT_BUBBLE, false);

    //     lv_obj_t * parent = lv_obj_get_parent(cont);
    //     if (parent) {
    //         lv_obj_send_event(parent, LV_EVENT_RELEASED, NULL);
    //     }
    // }

    // if (code == LV_EVENT_SCROLL_END) {
    //     lv_obj_set_flag(cont, LV_OBJ_FLAG_EVENT_BUBBLE, true);
    // }

    // if (code == LV_EVENT_PRESSED) {
    //     lv_obj_set_flag(cont, LV_OBJ_FLAG_EVENT_BUBBLE, false);
    // }

    // if (code == LV_EVENT_RELEASED) {
    //     lv_obj_set_flag(cont, LV_OBJ_FLAG_EVENT_BUBBLE, true);
    // }

}

static void on_control_drag_cb(lv_event_t * e)
{
    lv_obj_t *cont = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * home = lv_event_get_user_data(e);

    if (code == LV_EVENT_PRESSED) {
        panel_events_cb(LV_EVENT_PRESSED);
    }

    if (code == LV_EVENT_PRESSING) {
        panel_events_cb(LV_EVENT_PRESSING);
    }

    if (code == LV_EVENT_RELEASED || code == LV_EVENT_PRESS_LOST) {
        panel_events_cb(LV_EVENT_RELEASED);
    }

}

static void panel_events_cb(lv_event_code_t code)
{

    lv_indev_t * indev = lv_indev_active();

    if (code == LV_EVENT_PRESSED) {
        if(indev == NULL)  return;
        lv_point_t p;
        lv_indev_get_point(indev, &p);

        control_widget_home.start_y = p.y;
        control_widget_home.panel_y = lv_obj_get_y_aligned(control_widget_home.obj);
        control_widget_home.drag = true;
    }

    if (code == LV_EVENT_PRESSING && control_widget_home.drag) {

        if(indev == NULL)  return;
        lv_point_t vect;
        lv_indev_get_vect(indev, &vect);

        int32_t new_y = lv_obj_get_y_aligned(control_widget_home.obj) + vect.y;

        if (new_y > 0) new_y = 0;
        if (new_y < -control_widget_home.height) new_y = -control_widget_home.height;

        int32_t opa = lv_map(new_y, -control_widget_home.height, 0, 55, 255);
        lv_obj_set_style_bg_opa(control_widget_home.obj, opa, 0);

        lv_obj_set_y(control_widget_home.obj, new_y);
    }

    if (code == LV_EVENT_RELEASED && control_widget_home.drag) {

        control_widget_home.drag = false;

        int32_t y = lv_obj_get_y_aligned(control_widget_home.obj);
        int32_t threshold = control_widget_home.height / 5;

        /* Determine if drag exceeded threshold */
        if (LV_ABS(y - control_widget_home.panel_y) > threshold) {
            control_widget_home.open = !control_widget_home.open;
        }

        /* Animate to final state */
        int32_t target_y = control_widget_home.open ? 0 : -control_widget_home.height;
        lv_obj_animate_y(control_widget_home.obj, y, target_y, 200);

    }
}



static void home_screen_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *screen = lv_event_get_target(e);
    lv_indev_t * indev = lv_indev_active();


    if (code == LV_EVENT_PRESSED) {
        panel_events_cb(LV_EVENT_PRESSED);
    }

    if (code == LV_EVENT_PRESSING) {

        panel_events_cb(LV_EVENT_PRESSING);

    }

    if (code == LV_EVENT_RELEASED || code == LV_EVENT_PRESS_LOST) {

        panel_events_cb(LV_EVENT_RELEASED);

    }

}

static void lv_obj_animate_y(lv_obj_t *obj, int32_t start, int32_t end, int32_t duration)
{
    lv_anim_t   anim;
    lv_anim_init(&anim);

    /* Set the "animator" function */
    lv_anim_set_exec_cb(&anim, control_widget_cb);
    /* Set target of the Animation */
    lv_anim_set_var(&anim, obj);
    /* Length of the Animation [ms] */
    lv_anim_set_duration(&anim, duration);
    /* Set start and end values. E.g. 0, 150 */
    lv_anim_set_values(&anim, start, end);
    lv_anim_start(&anim);   /* Start the Animation */

}

static void screen_res_cb(lv_event_t *e)
{
    lv_display_t * disp = lv_event_get_target(e);
    int32_t w = lv_display_get_original_horizontal_resolution(disp);
    int32_t h = lv_display_get_original_vertical_resolution(disp);

    set_screen(w, h);
}

static void screen_gesture_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_GESTURE) return;

    gesture_map_t * data = lv_event_get_user_data(e);
    if (!data) return;   // protect user_data

    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());

    gesture_action_t * action = NULL;

    switch (dir) {
        case LV_DIR_LEFT:   action = &data->left;  break;
        case LV_DIR_RIGHT:  action = &data->right; break;
        case LV_DIR_TOP:    action = &data->up;    break;
        case LV_DIR_BOTTOM: action = &data->down;  break;
        default: return;
    }

    if (!action) return;

    if (!action->screen_fn) return;

    if (action->screen_fn) {
        lv_screen_load_anim(
            action->screen_fn(),
            action->anim,
            500,
            0,
            true
        );
    }
}

static void scroll_y_end_listener_cb(lv_event_t *e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    int32_t * scroll_pos = lv_event_get_user_data(e);
    *scroll_pos = lv_obj_get_scroll_y(obj);
}

static void scroll_x_end_listener_cb(lv_event_t *e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    int32_t * scroll_pos = lv_event_get_user_data(e);
    *scroll_pos = lv_obj_get_scroll_x(obj);
}


static lv_obj_t * get_list_from_wd(lv_obj_t * parent, const char * name)
{
    lv_obj_t * list = NULL;
    lv_obj_t * wd_list = lv_obj_find_by_name(parent, name);
    if (wd_list) {
        list = wd_list_get_container(wd_list);
    }
    return list;
}

static void settings_item_clicked_cb(lv_event_t * e)
{
    settings_item_create_cb_t function = (settings_item_create_cb_t)lv_event_get_user_data(e);
    lv_obj_t * screen = lv_obj_create(NULL);
    lv_obj_remove_style_all(screen);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_opa(screen, 255, 0);

    function(screen);

    static gesture_map_t gestures = {
        .left  = { NULL, 0 },
        .right = { screen_settings, LV_SCR_LOAD_ANIM_OUT_RIGHT },
        .up    = { NULL, 0 },
        .down  = { NULL, 0 },
    };

    lv_obj_add_event_cb(screen, screen_gesture_event_cb, LV_EVENT_GESTURE, &gestures);

    lv_screen_load_anim(screen, LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
    
}

static void settings_item_helper(lv_obj_t * parent, const void * icon,  const char * name, settings_item_create_cb_t function)
{
    lv_obj_t * item = app_item_create(parent, icon, name);
    lv_obj_add_event_cb(item, settings_item_clicked_cb, LV_EVENT_CLICKED, function);
}