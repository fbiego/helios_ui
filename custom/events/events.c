/**
 * @file events.c
 * @brief Events
 */

/*********************
*      INCLUDES
*********************/

#include "events.h"

#include "../../helios_ui_gen.h"
#include "../apps/app_init.h"
#include "../apps/app_screens.h"
#include "../subjects/subjects.h"
/*********************
*      DEFINES
*********************/

/**********************
*      TYPEDEFS
**********************/
typedef struct {
    int32_t parent_width;
    int32_t child1_width;
    int32_t child1_height;
    int32_t child2_width;
    bool overflow;
} hs_info_layout_state_t;

/***********************
*  STATIC VARIABLES
**********************/
extern bool notifications_to_apps;

static lv_obj_t * applications_list;
static lv_obj_t * contacts_wd_list;
static lv_obj_t * contacts_list;
static lv_obj_t * notifications_wd_list;
static lv_obj_t * notifications_list;
static lv_obj_t * stopwatch_lap_container;
static lv_obj_t * weather_hourly_row;
static lv_obj_t * weather_daily_column;

/***********************
*  STATIC PROTOTYPES
**********************/
static void applications_render_all(lv_obj_t * list);
static void applications_render_one(lv_obj_t * list, const helios_app_t * app);
static void applications_observer_cb(helios_apps_event_t event,
                                     const helios_app_t * app,
                                     void * user_data);
static void app_item_clicked_cb(lv_event_t * e);

static void contacts_render_all(lv_obj_t * list);
static void contacts_render_one(lv_obj_t * list, const helios_contact_t * contact);
static void contacts_observer_cb(helios_contacts_event_t event,
                                 const helios_contact_t * contact,
                                 void * user_data);

static void notifications_render_all(lv_obj_t * list);
static void notifications_render_one(lv_obj_t * list, const helios_notification_t * notification);
static void notifications_observer_cb(helios_notifications_event_t event,
                                      const helios_notification_t * notification,
                                      void * user_data);
static void notifications_clear_all_clicked_cb(lv_event_t * e);

static void stopwatch_render_laps(void);
static void stopwatch_start_clicked_cb(lv_event_t * e);
static void stopwatch_reset_clicked_cb(lv_event_t * e);

static void weather_render_all(void);
static void weather_render_hourly(lv_obj_t * parent, const helios_hourly_forecast_t * forecast);
static void weather_render_daily(lv_obj_t * parent, const helios_daily_forecast_t * forecast);
static void weather_set_hourly(lv_obj_t * obj, const helios_hourly_forecast_t * forecast);
static void weather_set_daily(lv_obj_t * obj, const helios_daily_forecast_t * forecast);
static void weather_observer_cb(helios_weather_event_t event, void * user_data);
static lv_obj_t * child_at(lv_obj_t * obj, int32_t index);
static void restore_scroll_y(lv_obj_t * obj, int32_t scroll_y);

/**********************
*   GLOBAL FUNCTIONS
**********************/

void on_settings_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_screen_load_anim(screen_settings(), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}

void on_weather_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_screen_load_anim(screen_weather(), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}

void on_notifications_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    notifications_to_apps = true;
    lv_screen_load_anim(screen_notifications(), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}

void on_contacts_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_screen_load_anim(screen_contacts(), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}

void on_navigation_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_screen_load_anim(simple_app_screen_create(navigation_create), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}

void on_music_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_screen_load_anim(simple_app_screen_create(music_create), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}

void on_phone_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_screen_load_anim(simple_app_screen_create(phone_create), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}

void on_simulator_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_SCREEN_LOADED) {
        lv_screen_load(screen_home());
    }
}

void helios_subject_music_package_change(const char * value)
{
    if (lv_streq("com.spotify.music", value)) {
        helios_subject_set_music_icon((void *)icon_spotify);
    } else {
        helios_subject_set_music_icon((void *)icon_music);
    }
}

void helios_subject_music_state_change(int32_t value)
{
    if (value) {
        helios_subject_set_music_state_icon((void *)icon_music_pause_32);
    } else {
        helios_subject_set_music_state_icon((void *)icon_music_play_32);
    }
}

void on_music_control_cb(lv_event_t *e)
{
    LV_UNUSED(e);
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
                   state->child2_width != width2 ||
                   state->child1_height != cont_h;
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
    } else {
        lv_obj_set_width(child1, LV_SIZE_CONTENT);
        lv_obj_set_width(child2, LV_SIZE_CONTENT);
        lv_obj_set_align(child2, LV_ALIGN_TOP_RIGHT);
        lv_obj_set_y(child2, 0);
    }
}

void screen_applications_events_cb(lv_event_t *e)
{
    lv_obj_t * applications = lv_event_get_current_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_SCREEN_LOAD_START) {
        applications_list = get_list_from_wd(applications, "app_list");
        applications_render_all(applications_list);
        helios_apps_observer_add(applications_observer_cb, NULL);
    }

    if (code == LV_EVENT_DELETE) {
        helios_apps_observer_remove(applications_observer_cb, NULL);
        applications_list = NULL;
    }
}

void screen_contacts_events_cb(lv_event_t *e)
{
    lv_obj_t * contacts = lv_event_get_current_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_SCREEN_LOAD_START) {
        contacts_wd_list = lv_obj_find_by_name(contacts, "contacts_list");
        contacts_list = get_list_from_wd(contacts, "contacts_list");
        contacts_render_all(contacts_list);
        helios_contacts_observer_add(contacts_observer_cb, NULL);
    }

    if (code == LV_EVENT_DELETE) {
        helios_contacts_observer_remove(contacts_observer_cb, NULL);
        contacts_wd_list = NULL;
        contacts_list = NULL;
    }
}

void screen_notifications_events_cb(lv_event_t *e)
{
    lv_obj_t * notifications = lv_event_get_current_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_SCREEN_LOAD_START) {
        LV_LOG_USER("Loading Notifications screen");

        notifications_wd_list = lv_obj_find_by_name(notifications, "notifications_list");
        notifications_list = get_list_from_wd(notifications, "notifications_list");
        notifications_render_all(notifications_list);
        helios_notifications_observer_add(notifications_observer_cb, NULL);
    }

    if (code == LV_EVENT_DELETE) {
        helios_notifications_observer_remove(notifications_observer_cb, NULL);
        notifications_wd_list = NULL;
        notifications_list = NULL;
    }
}

void screen_stopwatch_events_cb(lv_event_t *e)
{
    lv_obj_t * stopwatch = lv_event_get_current_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_SCREEN_LOAD_START) {
        stopwatch_lap_container = lv_obj_find_by_name(stopwatch, "lap_container");
        stopwatch_render_laps();
        helios_stopwatch_sync_subjects();

        lv_obj_t * root_container = child_at(stopwatch, 0);
        lv_obj_t * controls_column = child_at(root_container, 1);
        lv_obj_t * controls_row = child_at(controls_column, 0);
        lv_obj_t * reset_button = child_at(controls_row, 1);
        lv_obj_t * start_button = child_at(controls_row, 2);

        if (reset_button) {
            lv_obj_add_event_cb(reset_button, stopwatch_reset_clicked_cb, LV_EVENT_CLICKED, NULL);
        }

        if (start_button) {
            lv_obj_add_event_cb(start_button, stopwatch_start_clicked_cb, LV_EVENT_CLICKED, NULL);
        }
    }

    if (code == LV_EVENT_DELETE) {
        stopwatch_lap_container = NULL;
    }
}

void screen_weather_events_cb(lv_event_t *e)
{
    lv_obj_t * weather = lv_event_get_current_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_SCREEN_LOAD_START) {
        lv_obj_t * list = get_list_from_wd(weather, "weather_list");
        lv_obj_t * hourly_card = child_at(list, 1);
        lv_obj_t * daily_card = child_at(list, 2);

        weather_hourly_row = child_at(hourly_card, 2);
        weather_daily_column = child_at(daily_card, 1);

        weather_render_all();
        helios_weather_observer_add(weather_observer_cb, NULL);
    }

    if (code == LV_EVENT_DELETE) {
        helios_weather_observer_remove(weather_observer_cb, NULL);
        weather_hourly_row = NULL;
        weather_daily_column = NULL;
    }
}
/**********************
 *   STATIC FUNCTIONS
 **********************/

static void applications_render_all(lv_obj_t * list)
{
    if (!list) return;

    int32_t scroll_y = lv_obj_get_scroll_y(list);
    lv_obj_clean(list);

    uint32_t count = helios_apps_count();
    for (uint32_t i = 0; i < count; i++) {
        applications_render_one(list, helios_apps_get(i));
    }

    restore_scroll_y(list, scroll_y);
}

static void applications_render_one(lv_obj_t * list, const helios_app_t * app)
{
    if (!list || !app) return;

    lv_obj_t * item = app_item_create(list, app->icon, app->name, app->tag);
    if (app->create_cb) {
        lv_obj_add_event_cb(item, app_item_clicked_cb, LV_EVENT_CLICKED, (void *)app);
    }
}

static void applications_observer_cb(helios_apps_event_t event,
                                     const helios_app_t * app,
                                     void * user_data)
{
    LV_UNUSED(user_data);

    if (!applications_list) return;

    if (event == HELIOS_APPS_EVENT_ADDED) {
        applications_render_one(applications_list, app);
        return;
    }

    applications_render_all(applications_list);
}

static void app_item_clicked_cb(lv_event_t * e)
{
    const helios_app_t * app = lv_event_get_user_data(e);
    helios_apps_launch(app);
}

static void contacts_render_all(lv_obj_t * list)
{
    if (!list) return;

    uint32_t count = helios_contacts_count();
    if (contacts_wd_list) {
        if (count == 0) lv_obj_add_flag(list, LV_OBJ_FLAG_HIDDEN);
        else lv_obj_remove_flag(list, LV_OBJ_FLAG_HIDDEN);
    }

    int32_t scroll_y = lv_obj_get_scroll_y(list);
    lv_obj_clean(list);

    for (uint32_t i = 0; i < count; i++) {
        contacts_render_one(list, helios_contacts_get(i));
    }

    restore_scroll_y(list, scroll_y);
}

static void contacts_render_one(lv_obj_t * list, const helios_contact_t * contact)
{
    if (!list || !contact) return;

    if (contacts_wd_list) lv_obj_remove_flag(contacts_wd_list, LV_OBJ_FLAG_HIDDEN);
    contact_item_create(list, contact->name, contact->number);
}

static void contacts_observer_cb(helios_contacts_event_t event,
                                 const helios_contact_t * contact,
                                 void * user_data)
{
    LV_UNUSED(user_data);

    if (!contacts_list) return;

    if (event == HELIOS_CONTACTS_EVENT_ADDED) {
        contacts_render_one(contacts_list, contact);
        return;
    }

    contacts_render_all(contacts_list);
}

static void notifications_render_all(lv_obj_t * list)
{
    if (!list) return;

    uint32_t count = helios_notifications_count();
    if (notifications_wd_list) {
        if (count == 0) lv_obj_add_flag(list, LV_OBJ_FLAG_HIDDEN);
        else lv_obj_remove_flag(list, LV_OBJ_FLAG_HIDDEN);
    }

    int32_t scroll_y = lv_obj_get_scroll_y(list);
    lv_obj_clean(list);

    if (count > 0) {
        lv_obj_t * clear_all = hs_button_create(list, "Clear All", "clear_all", COLOR_DANGER);
        lv_obj_set_style_bg_color(clear_all, COLOR_BUTTON_DANGER, 0);
        lv_obj_set_style_radius(clear_all, 40, 0);
        lv_obj_add_event_cb(clear_all, notifications_clear_all_clicked_cb, LV_EVENT_CLICKED, NULL);
    }

    for (uint32_t i = 0; i < count; i++) {
        notifications_render_one(list, helios_notifications_get(i));
    }

    restore_scroll_y(list, scroll_y);
}

static void notifications_render_one(lv_obj_t * list, const helios_notification_t * notification)
{
    if (!list || !notification) return;

    if (notifications_wd_list) lv_obj_remove_flag(notifications_wd_list, LV_OBJ_FLAG_HIDDEN);
    notification_item_create(list,
                             notification->icon,
                             notification->title,
                             notification->time,
                             notification->message);
}

static void notifications_observer_cb(helios_notifications_event_t event,
                                      const helios_notification_t * notification,
                                      void * user_data)
{
    LV_UNUSED(user_data);

    if (!notifications_list) return;

    LV_UNUSED(notification);
    notifications_render_all(notifications_list);
}

static void notifications_clear_all_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    helios_notifications_clear();
}

static void stopwatch_render_laps(void)
{
    if (!stopwatch_lap_container) return;

    int32_t scroll_y = lv_obj_get_scroll_y(stopwatch_lap_container);
    lv_obj_clean(stopwatch_lap_container);

    uint32_t count = helios_stopwatch_lap_count();
    for (uint32_t i = 0; i < count; i++) {
        const helios_stopwatch_lap_t * lap = helios_stopwatch_lap_get(count - i - 1);
        if (lap) hs_lap_item_create(stopwatch_lap_container, lap->title, lap->time);
    }

    restore_scroll_y(stopwatch_lap_container, scroll_y);
}

static void stopwatch_start_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);

    helios_stopwatch_toggle();
}

static void stopwatch_reset_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);

    helios_stopwatch_lap_or_reset();
    stopwatch_render_laps();
}

static void weather_render_all(void)
{
    if (weather_hourly_row) {
        int32_t scroll_x = lv_obj_get_scroll_x(weather_hourly_row);
        lv_obj_clean(weather_hourly_row);

        uint32_t hourly_count = helios_weather_hourly_count();
        for (uint32_t i = 0; i < hourly_count; i++) {
            weather_render_hourly(weather_hourly_row, helios_weather_hourly_get(i));
        }

        lv_obj_scroll_to_x(weather_hourly_row, scroll_x, LV_ANIM_OFF);
    }

    if (weather_daily_column) {
        int32_t scroll_y = lv_obj_get_scroll_y(weather_daily_column);
        lv_obj_clean(weather_daily_column);

        uint32_t daily_count = helios_weather_daily_count();
        for (uint32_t i = 0; i < daily_count; i++) {
            weather_render_daily(weather_daily_column, helios_weather_daily_get(i));
        }

        restore_scroll_y(weather_daily_column, scroll_y);
    }
}

static void weather_render_hourly(lv_obj_t * parent, const helios_hourly_forecast_t * forecast)
{
    if (!parent || !forecast) return;

    lv_obj_t * obj = hourly_forecast_create(parent);
    weather_set_hourly(obj, forecast);
}

static void weather_render_daily(lv_obj_t * parent, const helios_daily_forecast_t * forecast)
{
    if (!parent || !forecast) return;

    lv_obj_t * obj = daily_forecast_create(parent);
    weather_set_daily(obj, forecast);
}

static void weather_set_hourly(lv_obj_t * obj, const helios_hourly_forecast_t * forecast)
{
    if (!obj || !forecast) return;

    lv_obj_t * time = child_at(obj, 0);
    lv_obj_t * icon = child_at(obj, 1);
    lv_obj_t * temp = child_at(obj, 2);
    lv_obj_t * humidity = child_at(obj, 3);

    if (time) lv_label_set_text(time, forecast->time);
    if (icon) wd_image_set_src(icon, forecast->icon);
    if (temp) lv_label_set_text(temp, forecast->temp);
    if (humidity) lv_label_set_text(humidity, forecast->humidity);
}

static void weather_set_daily(lv_obj_t * obj, const helios_daily_forecast_t * forecast)
{
    if (!obj || !forecast) return;

    lv_obj_t * day = child_at(obj, 0);
    lv_obj_t * icon = child_at(obj, 1);
    lv_obj_t * temp = child_at(obj, 2);

    if (day) lv_label_set_text(day, forecast->day);
    if (icon) wd_image_set_src(icon, forecast->icon);
    if (temp) lv_label_set_text(temp, forecast->temp);
}

static void weather_observer_cb(helios_weather_event_t event, void * user_data)
{
    LV_UNUSED(event);
    LV_UNUSED(user_data);

    weather_render_all();
}

static lv_obj_t * child_at(lv_obj_t * obj, int32_t index)
{
    if (!obj || index < 0 || index >= (int32_t)lv_obj_get_child_count(obj)) return NULL;
    return lv_obj_get_child(obj, index);
}

static void restore_scroll_y(lv_obj_t * obj, int32_t scroll_y)
{
    if (!obj) return;
    lv_obj_scroll_to_y(obj, scroll_y, LV_ANIM_OFF);
}
