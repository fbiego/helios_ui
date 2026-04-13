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

typedef struct {
    int32_t parent_width;
    int32_t child1_width;
    int32_t child1_height;
    int32_t child2_width;
    bool overflow;
} hs_info_layout_state_t;

typedef lv_obj_t * (*settings_item_create_cb_t)(lv_obj_t * parent);

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void on_language_change(lv_event_t * e);
static void language_observer_cb(lv_observer_t *observer, lv_subject_t *subject);

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

// void set_emoji_fallback(lv_font_t * font);

/**********************
 *  STATIC VARIABLES
 **********************/
static control_panel_t control_widget_home;

static bool notifications_to_apps = false;

static lv_font_t NS_Medium_14_rt;
static lv_font_t NS_Medium_16_rt;
static lv_font_t NS_Medium_18_rt;
static lv_font_t NS_Medium_20_rt;
static lv_font_t NS_Medium_30_rt;
static lv_font_t NS_Medium_40_rt;

extern lv_font_t NS_Medium_14_data;
extern lv_font_t NS_Medium_16_data;
extern lv_font_t NS_Medium_18_data;
extern lv_font_t NS_Medium_20_data;
extern lv_font_t NS_Medium_30_data;
extern lv_font_t NS_Medium_40_data;

extern lv_style_t style_text_small_466;
extern lv_style_t style_text_small_360;
extern lv_style_t style_text_small_240;
extern lv_style_t style_text_normal_466;
extern lv_style_t style_text_normal_360;
extern lv_style_t style_text_normal_240;
extern lv_style_t style_text_large_466;
extern lv_style_t style_text_large_360;
extern lv_style_t style_text_large_240;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void helios_ui_init(const char * asset_path)
{
    helios_ui_init_gen(asset_path);

    NS_Medium_14_rt = NS_Medium_14_data;
    NS_Medium_16_rt = NS_Medium_16_data;
    NS_Medium_18_rt = NS_Medium_18_data;
    NS_Medium_20_rt = NS_Medium_20_data;
    NS_Medium_30_rt = NS_Medium_30_data;
    NS_Medium_40_rt = NS_Medium_40_data;

    NS_Medium_14 = &NS_Medium_14_rt;
    NS_Medium_16 = &NS_Medium_16_rt;
    NS_Medium_18 = &NS_Medium_18_rt;
    NS_Medium_20 = &NS_Medium_20_rt;
    NS_Medium_30 = &NS_Medium_30_rt;
    NS_Medium_40 = &NS_Medium_40_rt;

    lv_style_set_text_font(&style_text_small_466, NS_Medium_20);
    lv_style_set_text_font(&style_text_small_360, NS_Medium_18);
    lv_style_set_text_font(&style_text_small_240, NS_Medium_14);
    lv_style_set_text_font(&style_text_normal_466, NS_Medium_40);
    lv_style_set_text_font(&style_text_normal_360, NS_Medium_30);
    lv_style_set_text_font(&style_text_normal_240, NS_Medium_20);

    // font_fallback_init();

    /* Add your own custom code here if needed */

    lv_obj_add_event_cb(lv_screen_active(), on_language_change, LV_EVENT_TRANSLATION_LANGUAGE_CHANGED, NULL);

    lv_subject_add_observer(&sb_language, language_observer_cb, NULL);
    
#if defined(LV_EDITOR_PREVIEW)
    lv_display_t *disp = lv_display_get_default();
    if (disp) {
        lv_display_add_event_cb(disp, screen_res_cb, LV_EVENT_RESOLUTION_CHANGED, NULL);
        lv_display_send_event(disp, LV_EVENT_RESOLUTION_CHANGED, NULL);
    }
#endif

}

void font_fallback_update(void)
{

    const char * lan =  lv_translation_get_language();
    
    if(lv_streq("de", lan) || lv_streq("fr", lan) || lv_streq("es", lan) || 
        lv_streq("pt", lan) || lv_streq("hu", lan)) {
        NS_Medium_14->fallback = NS_Medium_latin_14;
        NS_Medium_16->fallback = NS_Medium_latin_16;
        NS_Medium_18->fallback = NS_Medium_latin_18;
        NS_Medium_20->fallback = NS_Medium_latin_20;
        NS_Medium_30->fallback = NS_Medium_latin_30;
        NS_Medium_40->fallback = NS_Medium_latin_40;
    }
    else if(lv_streq("ru", lan)) {
        NS_Medium_14->fallback = NS_Medium_ru_14;
        NS_Medium_16->fallback = NS_Medium_ru_16;
        NS_Medium_18->fallback = NS_Medium_ru_18;
        NS_Medium_20->fallback = NS_Medium_ru_20;
        NS_Medium_30->fallback = NS_Medium_ru_30;
        NS_Medium_40->fallback = NS_Medium_ru_40;
    }
    else if(lv_streq("ja", lan)) {
        NS_Medium_14->fallback = NS_Medium_jp_14;
        NS_Medium_16->fallback = NS_Medium_jp_16;
        NS_Medium_18->fallback = NS_Medium_jp_18;
        NS_Medium_20->fallback = NS_Medium_jp_20;
        NS_Medium_30->fallback = NS_Medium_jp_30;
        NS_Medium_40->fallback = NS_Medium_jp_40;
    }
    else if(lv_streq("zh", lan)) {
        NS_Medium_14->fallback = NS_Medium_zh_14;
        NS_Medium_16->fallback = NS_Medium_zh_16;
        NS_Medium_18->fallback = NS_Medium_zh_18;
        NS_Medium_20->fallback = NS_Medium_zh_20;
        NS_Medium_30->fallback = NS_Medium_zh_30;
        NS_Medium_40->fallback = NS_Medium_zh_40;
    }
    else if(lv_streq("th", lan)) {
        NS_Medium_14->fallback = NS_Medium_th_14;
        NS_Medium_16->fallback = NS_Medium_th_16;
        NS_Medium_18->fallback = NS_Medium_th_18;
        NS_Medium_20->fallback = NS_Medium_th_20;
        NS_Medium_30->fallback = NS_Medium_th_30;
        NS_Medium_40->fallback = NS_Medium_th_40;
    } 
    else if(lv_streq("el", lan)) {
        NS_Medium_14->fallback = NS_Medium_el_14;
        NS_Medium_16->fallback = NS_Medium_el_16;
        NS_Medium_18->fallback = NS_Medium_el_18;
        NS_Medium_20->fallback = NS_Medium_el_20;
        NS_Medium_30->fallback = NS_Medium_el_30;
        NS_Medium_40->fallback = NS_Medium_el_40;
    } else if(lv_streq("hi", lan)) {
        NS_Medium_14->fallback = NS_Medium_hi_14;
        NS_Medium_16->fallback = NS_Medium_hi_16;
        NS_Medium_18->fallback = NS_Medium_hi_18;
        NS_Medium_20->fallback = NS_Medium_hi_20;
        NS_Medium_30->fallback = NS_Medium_hi_30;
        NS_Medium_40->fallback = NS_Medium_hi_40;
    } else {
        NS_Medium_14->fallback = NULL;
        NS_Medium_16->fallback = NULL;
        NS_Medium_18->fallback = NULL;
        NS_Medium_20->fallback = NULL;
        NS_Medium_30->fallback = NULL;
        NS_Medium_40->fallback = NULL;
    }

    // set_emoji_fallback(NS_Medium_14);
    // set_emoji_fallback(NS_Medium_16);
    // set_emoji_fallback(NS_Medium_18);
    // set_emoji_fallback(NS_Medium_20);
    // set_emoji_fallback(NS_Medium_30);
    // set_emoji_fallback(NS_Medium_40);


}

// void set_emoji_fallback(lv_font_t * font) 
// {

//     if (font->fallback == NULL) {
//         font->fallback = NS_Medium_emoji_16;
//     } else {
//         NS_Medium_emoji_16->fallback = font->fallback;
//         font->fallback = NS_Medium_emoji_16;
//     }
// }

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

        settings_item_helper(list, icon_settings_monitor, "display", settings_display_create);
        settings_item_helper(list, icon_settings_smartwatch, "system", settings_system_create);
        settings_item_helper(list, icon_settings_bell, "alerts", settings_alert_create);
        settings_item_helper(list, icon_settings_power, "battery", settings_battery_create);
        settings_item_helper(list, icon_settings_harddisk, "storage", settings_storage_create);
        settings_item_helper(list, icon_settings_information, "about", settings_about_create);

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

static void on_language_change(lv_event_t * e)
{
    const char * language = lv_event_get_param(e);
    LV_LOG_USER("Language changed to %s", language);
}

static void language_observer_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    int32_t index = lv_subject_get_int(subject);
    LV_LOG_USER("Language index %d", index);

    switch(index) {
        case 0: lv_translation_set_language("en"); break;
        case 1: lv_translation_set_language("ru"); break;
        case 2: lv_translation_set_language("pt"); break;
        case 3: lv_translation_set_language("el"); break;
        case 4: lv_translation_set_language("de"); break;
        case 5: lv_translation_set_language("es"); break;
        case 6: lv_translation_set_language("fr"); break;
        case 7: lv_translation_set_language("zh"); break;
        case 8: lv_translation_set_language("hi"); break;
        case 9: lv_translation_set_language("ja"); break;
        case 10: lv_translation_set_language("th"); break;
        case 11: lv_translation_set_language("hu"); break;
    }
    font_fallback_update();
}
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
    lv_obj_t * item = app_item_create(parent, icon, name, name);
    lv_obj_add_event_cb(item, settings_item_clicked_cb, LV_EVENT_CLICKED, function);
}

void on_hs_info_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_DELETE) {
        hs_info_layout_state_t * state = lv_obj_get_user_data(obj);
        if (state) {
            lv_free(state);
            lv_obj_set_user_data(obj, NULL);
        }
        return;
    }

    if (code != LV_EVENT_GET_SELF_SIZE) return;

    int32_t count = lv_obj_get_child_cnt(obj);
    int32_t p_width = lv_obj_get_width(obj);
    if (count != 2 || p_width == 0) return;

    lv_obj_t * child1 = lv_obj_get_child(obj, 0);
    lv_obj_t * child2 = lv_obj_get_child(obj, 1);

    int32_t width1 = lv_obj_get_width(child1);
    int32_t width2 = lv_obj_get_width(child2);

    lv_area_t cont_a;
    lv_obj_get_coords(child1, &cont_a);
    int32_t cont_h = lv_area_get_height(&cont_a);
    // LV_LOG_USER("Child1 height: %d", cont_h);

    if (width1 == 0 || width2 == 0) return;

    hs_info_layout_state_t * state = lv_obj_get_user_data(obj);
    if (state == NULL) {
        state = lv_malloc(sizeof(*state));
        if (state == NULL) return;

        state->parent_width = 0;
        state->child1_width = 0;
        state->child1_height = 0;
        state->child2_width = 0;
        state->overflow = false;
        lv_obj_set_user_data(obj, state);
    }

    bool forced_overflow_widths = state->overflow && width1 == p_width && width2 == p_width;
    if (forced_overflow_widths) {
        width1 = state->child1_width;
        width2 = state->child2_width;
    }

    bool changed = state->parent_width != p_width ||
                   state->child1_width != width1 ||
                   state->child2_width != width2 || state->child1_height != cont_h;
    if (!changed) return;

    bool overflow = width1 + width2 > p_width;

    state->parent_width = p_width;
    state->child1_width = width1;
    state->child2_width = width2;
    state->overflow = overflow;
    state->child1_height = cont_h;

    if (overflow) {
        lv_obj_set_width(child1, lv_pct(100));
        lv_obj_set_width(child2, lv_pct(100));
        lv_obj_update_layout(child1);

        lv_obj_set_y(child2, state->child1_height);

        // LV_LOG_USER("Overflow detected: width1=%d, height1=%d, width2=%d, parent_width=%d", width1, state->child1_height, width2, p_width);
    } else {
        lv_obj_set_width(child1, LV_SIZE_CONTENT);
        lv_obj_set_width(child2, LV_SIZE_CONTENT);
        lv_obj_set_align(child2, LV_ALIGN_TOP_RIGHT);
        lv_obj_set_y(child2, 0);
    }
}
