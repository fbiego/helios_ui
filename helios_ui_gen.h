/**
 * @file helios_ui_gen.h
 */

#ifndef HELIOS_UI_GEN_H
#define HELIOS_UI_GEN_H

#ifndef UI_SUBJECT_STRING_LENGTH
#define UI_SUBJECT_STRING_LENGTH 256
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
    #include "lvgl_private.h"
#else
    #include "lvgl/lvgl.h"
    #include "lvgl/lvgl_private.h"
#endif



/*********************
 *      DEFINES
 *********************/

#define COLOR_PRIMARY lv_color_hex(0x0534ff)

#define COLOR_DANGER lv_color_hex(0xf62525)

#define COLOR_BUTTON_PRIMARY lv_color_hex(0x181146)

#define COLOR_BUTTON_DANGER lv_color_hex(0x2c0d0b)

#define UI_VERSION "v0.0.1"

/**********************
 *      TYPEDEFS
 **********************/

typedef enum {
    SCREEN_SIZE_SC_466 = 0,
    SCREEN_SIZE_SC_360 = 1,
    SCREEN_SIZE_SC_240 = 2
}screen_size_t;

/**********************
 * GLOBAL VARIABLES
 **********************/

/*-------------------
 * Permanent screens
 *------------------*/

/*----------------
 * Global styles
 *----------------*/

extern lv_style_t style_dark;
extern lv_style_t style_primary_bg;
extern lv_style_t style_white_bg;
extern lv_style_t style_icon_recolor;
extern lv_style_t style_text_small_466;
extern lv_style_t style_text_small_360;
extern lv_style_t style_text_small_240;
extern lv_style_t style_text_normal_466;
extern lv_style_t style_text_normal_360;
extern lv_style_t style_text_normal_240;
extern lv_style_t style_text_large_466;
extern lv_style_t style_text_large_360;
extern lv_style_t style_text_large_240;

/*----------------
 * Fonts
 *----------------*/

extern lv_font_t * NS_Medium_70;

extern lv_font_t * NS_Medium_100;

extern lv_font_t * NS_Medium_140;

extern lv_font_t * NS_Medium_14;

extern lv_font_t * NS_Medium_16;

extern lv_font_t * NS_Medium_18;

extern lv_font_t * NS_Medium_20;

extern lv_font_t * NS_Medium_30;

extern lv_font_t * NS_Medium_40;

extern lv_font_t * NS_Medium_latin_14;

extern lv_font_t * NS_Medium_latin_16;

extern lv_font_t * NS_Medium_latin_18;

extern lv_font_t * NS_Medium_latin_20;

extern lv_font_t * NS_Medium_latin_30;

extern lv_font_t * NS_Medium_latin_40;

extern lv_font_t * NS_Medium_ru_14;

extern lv_font_t * NS_Medium_ru_16;

extern lv_font_t * NS_Medium_ru_18;

extern lv_font_t * NS_Medium_ru_20;

extern lv_font_t * NS_Medium_ru_30;

extern lv_font_t * NS_Medium_ru_40;

extern lv_font_t * NS_Medium_el_14;

extern lv_font_t * NS_Medium_el_16;

extern lv_font_t * NS_Medium_el_18;

extern lv_font_t * NS_Medium_el_20;

extern lv_font_t * NS_Medium_el_30;

extern lv_font_t * NS_Medium_el_40;

extern lv_font_t * NS_Medium_hi_14;

extern lv_font_t * NS_Medium_hi_16;

extern lv_font_t * NS_Medium_hi_18;

extern lv_font_t * NS_Medium_hi_20;

extern lv_font_t * NS_Medium_hi_30;

extern lv_font_t * NS_Medium_hi_40;

extern lv_font_t * NS_Medium_th_14;

extern lv_font_t * NS_Medium_th_16;

extern lv_font_t * NS_Medium_th_18;

extern lv_font_t * NS_Medium_th_20;

extern lv_font_t * NS_Medium_th_30;

extern lv_font_t * NS_Medium_th_40;

extern lv_font_t * NS_Medium_zh_14;

extern lv_font_t * NS_Medium_zh_16;

extern lv_font_t * NS_Medium_zh_18;

extern lv_font_t * NS_Medium_zh_20;

extern lv_font_t * NS_Medium_zh_30;

extern lv_font_t * NS_Medium_zh_40;

extern lv_font_t * NS_Medium_jp_14;

extern lv_font_t * NS_Medium_jp_16;

extern lv_font_t * NS_Medium_jp_18;

extern lv_font_t * NS_Medium_jp_20;

extern lv_font_t * NS_Medium_jp_30;

extern lv_font_t * NS_Medium_jp_40;

/*----------------
 * Images
 *----------------*/

extern const void * icon_empty;
extern const void * icon_wifi;
extern const void * icon_list;
extern const void * icon_brightness_full;
extern const void * icon_brightness_empty;
extern const void * icon_volume_high;
extern const void * icon_volume_low;
extern const void * icon_mute;
extern const void * icon_play;
extern const void * icon_back;
extern const void * icon_next;
extern const void * icon_connect;
extern const void * icon_vibration;
extern const void * icon_dnd;
extern const void * icon_qr;
extern const void * icon_arrow_up;
extern const void * icon_turn_left;
extern const void * icon_settings_harddisk;
extern const void * icon_settings_brightness;
extern const void * icon_settings_monitor;
extern const void * icon_settings_information;
extern const void * icon_settings_smartwatch;
extern const void * icon_settings_rotate;
extern const void * icon_settings_power;
extern const void * icon_settings_bell;
extern const void * icon_application;
extern const void * icon_chat;
extern const void * icon_weather;
extern const void * icon_gear;
extern const void * icon_measurement;
extern const void * icon_stopwatch;
extern const void * icon_contacts;
extern const void * icon_navigation;
extern const void * icon_timer;
extern const void * icon_music;
extern const void * icon_folder;
extern const void * icon_running;
extern const void * icon_sleep;
extern const void * icon_user;
extern const void * icon_weather_humidity_icon;
extern const void * icon_weather_temp_up_icon;
extern const void * icon_weather_temp_down_icon;
extern const void * icon_weather_uv_icon;

/*----------------
 * Subjects
 *----------------*/

extern lv_subject_t sb_screen_size;
extern lv_subject_t sb_screen_type;
extern lv_subject_t sb_screen_width;
extern lv_subject_t sb_screen_height;
extern lv_subject_t sb_screen_res;
extern lv_subject_t sb_placeholder;
extern lv_subject_t sb_lvgl_version;
extern lv_subject_t sb_app_list_mode;
extern lv_subject_t sb_list_circular_mode;
extern lv_subject_t sb_screen_brightness;
extern lv_subject_t sb_screen_rotation;
extern lv_subject_t sb_screen_timeout;
extern lv_subject_t sb_screen_rtw;
extern lv_subject_t sb_language;
extern lv_subject_t sb_battery_percent;
extern lv_subject_t sb_sound_volume;
extern lv_subject_t sb_focusable;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*----------------
 * Event Callbacks
 *----------------*/

void on_hs_info_cb(lv_event_t * e);
void on_contacts_clicked_cb(lv_event_t * e);
void on_navigation_clicked_cb(lv_event_t * e);
void on_notifications_clicked_cb(lv_event_t * e);
void on_settings_clicked_cb(lv_event_t * e);
void on_weather_clicked_cb(lv_event_t * e);
void on_simulator_event_cb(lv_event_t * e);

/**
 * Initialize the component library
 */

void helios_ui_init_gen(const char * asset_path);

/**********************
 *      MACROS
 **********************/

/**********************
 *   POST INCLUDES
 **********************/

/*Include all the widgets, components and screens of this library*/
#include "components/control/control_bar/control_bar_gen.h"
#include "components/control/control_button/control_button_gen.h"
#include "components/control/control_group/control_group_gen.h"
#include "components/control/control_music/control_music_gen.h"
#include "components/control/control_panel/control_panel_gen.h"
#include "components/control/control_slider/control_slider_gen.h"
#include "components/control/control_switch/control_switch_gen.h"
#include "components/dialogs/info_dialog/info_dialog_gen.h"
#include "components/generic/hs_bar/hs_bar_gen.h"
#include "components/generic/hs_button_icon/hs_button_icon_gen.h"
#include "components/generic/hs_button_text/hs_button_text_gen.h"
#include "components/generic/hs_button/hs_button_gen.h"
#include "components/generic/hs_card/hs_card_gen.h"
#include "components/generic/hs_column/hs_column_gen.h"
#include "components/generic/hs_dropdown_item/hs_dropdown_item_gen.h"
#include "components/generic/hs_dropdown/hs_dropdown_gen.h"
#include "components/generic/hs_info_sb/hs_info_sb_gen.h"
#include "components/generic/hs_info/hs_info_gen.h"
#include "components/generic/hs_line/hs_line_gen.h"
#include "components/generic/hs_roller/hs_roller_gen.h"
#include "components/generic/hs_row/hs_row_gen.h"
#include "components/generic/hs_slider/hs_slider_gen.h"
#include "components/generic/hs_space/hs_space_gen.h"
#include "components/generic/hs_switch/hs_switch_gen.h"
#include "components/generic/hs_text_icon/hs_text_icon_normal/hs_text_icon_normal_gen.h"
#include "components/generic/hs_text/hs_text_large/hs_text_large_gen.h"
#include "components/generic/hs_text/hs_text_medium/hs_text_medium_gen.h"
#include "components/generic/hs_text/hs_text_normal/hs_text_normal_gen.h"
#include "components/generic/hs_text/hs_text_small/hs_text_small_gen.h"
#include "components/generic/hs_title/hs_title_gen.h"
#include "components/items/app_item/app_item_gen.h"
#include "components/items/contact_item/contact_item_gen.h"
#include "components/items/notification_item/notification_item_gen.h"
#include "components/settings/settings_about/settings_about_gen.h"
#include "components/settings/settings_alert/settings_alert_gen.h"
#include "components/settings/settings_battery/settings_battery_gen.h"
#include "components/settings/settings_display/settings_display_gen.h"
#include "components/settings/settings_storage/settings_storage_gen.h"
#include "components/settings/settings_system/settings_system_gen.h"
#include "components/watchfaces/watchface_default/watchface_default_gen.h"
#include "components/weather/daily_forecast/daily_forecast_gen.h"
#include "components/weather/hourly_forecast/hourly_forecast_gen.h"
#include "components/weather/weather_widget/weather_widget_gen.h"
#include "screens/core/applications/applications_gen.h"
#include "screens/core/boot/boot_gen.h"
#include "screens/core/contacts/contacts_gen.h"
#include "screens/core/home/home_gen.h"
#include "screens/core/navigation/navigation_gen.h"
#include "screens/core/notifications/notifications_gen.h"
#include "screens/core/settings/settings_gen.h"
#include "screens/core/weather/weather_gen.h"
#include "screens/core/widgets/widgets_gen.h"
#include "screens/simulator/simulator_gen.h"
#include "widgets/wd_arcoiris/wd_arcoiris_gen.h"
#include "widgets/wd_dropdown/wd_dropdown_gen.h"
#include "widgets/wd_image/wd_image_gen.h"
#include "widgets/wd_list/wd_list_gen.h"
#include "widgets/wd_segment/wd_segment_gen.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*HELIOS_UI_GEN_H*/