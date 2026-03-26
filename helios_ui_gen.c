/**
 * @file helios_ui_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "helios_ui_gen.h"

#if LV_USE_XML
#include "widgets/wd_arcoiris/wd_arcoiris_private_gen.h"
#include "widgets/wd_image/wd_image_private_gen.h"
#include "widgets/wd_list/wd_list_private_gen.h"
#endif /* LV_USE_XML */

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/*----------------
 * Translations
 *----------------*/

/**********************
 *  GLOBAL VARIABLES
 **********************/

/*--------------------
 *  Permanent screens
 *-------------------*/

/*----------------
 * Fonts
 *----------------*/

lv_font_t * NS_Medium_14;
extern lv_font_t NS_Medium_14_data;
lv_font_t * NS_Medium_16;
extern lv_font_t NS_Medium_16_data;
lv_font_t * NS_Medium_18;
extern lv_font_t NS_Medium_18_data;
lv_font_t * NS_Medium_20;
extern lv_font_t NS_Medium_20_data;
lv_font_t * NS_Medium_30;
extern lv_font_t NS_Medium_30_data;
lv_font_t * NS_Medium_40;
extern lv_font_t NS_Medium_40_data;
lv_font_t * NS_Medium_70;
extern lv_font_t NS_Medium_70_data;
lv_font_t * NS_Medium_100;
extern lv_font_t NS_Medium_100_data;
lv_font_t * NS_Medium_140;
extern lv_font_t NS_Medium_140_data;

/*----------------
 * Images
 *----------------*/

const void * icon_empty;
extern const void * icon_empty_data;
const void * icon_wifi;
extern const void * icon_wifi_data;
const void * icon_list;
extern const void * icon_list_data;
const void * icon_brightness_full;
extern const void * icon_brightness_full_data;
const void * icon_brightness_empty;
extern const void * icon_brightness_empty_data;
const void * icon_volume_high;
extern const void * icon_volume_high_data;
const void * icon_volume_low;
extern const void * icon_volume_low_data;
const void * icon_mute;
extern const void * icon_mute_data;
const void * icon_play;
extern const void * icon_play_data;
const void * icon_back;
extern const void * icon_back_data;
const void * icon_next;
extern const void * icon_next_data;
const void * icon_connect;
extern const void * icon_connect_data;
const void * icon_vibration;
extern const void * icon_vibration_data;
const void * icon_dnd;
extern const void * icon_dnd_data;
const void * icon_qr;
extern const void * icon_qr_data;
const void * icon_settings_harddisk;
extern const void * icon_settings_harddisk_data;
const void * icon_settings_brightness;
extern const void * icon_settings_brightness_data;
const void * icon_settings_monitor;
extern const void * icon_settings_monitor_data;
const void * icon_settings_information;
extern const void * icon_settings_information_data;
const void * icon_settings_smartwatch;
extern const void * icon_settings_smartwatch_data;
const void * icon_settings_rotate;
extern const void * icon_settings_rotate_data;
const void * icon_settings_power;
extern const void * icon_settings_power_data;
const void * icon_settings_bell;
extern const void * icon_settings_bell_data;
const void * icon_application;
extern const void * icon_application_data;
const void * icon_chat;
extern const void * icon_chat_data;
const void * icon_weather;
extern const void * icon_weather_data;
const void * icon_gear;
extern const void * icon_gear_data;
const void * icon_measurement;
extern const void * icon_measurement_data;
const void * icon_stopwatch;
extern const void * icon_stopwatch_data;
const void * icon_contacts;
extern const void * icon_contacts_data;
const void * icon_navigation;
extern const void * icon_navigation_data;
const void * icon_timer;
extern const void * icon_timer_data;
const void * icon_music;
extern const void * icon_music_data;
const void * icon_folder;
extern const void * icon_folder_data;
const void * icon_running;
extern const void * icon_running_data;
const void * icon_sleep;
extern const void * icon_sleep_data;

/*----------------
 * Global styles
 *----------------*/

lv_style_t style_dark;
lv_style_t style_primary_bg;
lv_style_t style_white_bg;
lv_style_t style_icon_recolor;
lv_style_t style_text_small_466;
lv_style_t style_text_small_360;
lv_style_t style_text_small_240;
lv_style_t style_text_normal_466;
lv_style_t style_text_normal_360;
lv_style_t style_text_normal_240;
lv_style_t style_text_large_466;
lv_style_t style_text_large_360;
lv_style_t style_text_large_240;

/*----------------
 * Subjects
 *----------------*/

lv_subject_t sb_screen_size;
lv_subject_t sb_screen_type;
lv_subject_t sb_app_list_mode;
lv_subject_t sb_list_circular_mode;
lv_subject_t sb_screen_brightness;
lv_subject_t sb_screen_rotation;
lv_subject_t sb_screen_timeout;
lv_subject_t sb_screen_rtw;
lv_subject_t sb_battery_percent;
lv_subject_t sb_sound_volume;
lv_subject_t sb_focusable;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void helios_ui_init_gen(const char * asset_path)
{
    char buf[256];


    /*----------------
     * Fonts
     *----------------*/

    /* get font 'NS_Medium_14' from a C array */
    NS_Medium_14 = &NS_Medium_14_data;
    /* get font 'NS_Medium_16' from a C array */
    NS_Medium_16 = &NS_Medium_16_data;
    /* get font 'NS_Medium_18' from a C array */
    NS_Medium_18 = &NS_Medium_18_data;
    /* get font 'NS_Medium_20' from a C array */
    NS_Medium_20 = &NS_Medium_20_data;
    /* get font 'NS_Medium_30' from a C array */
    NS_Medium_30 = &NS_Medium_30_data;
    /* get font 'NS_Medium_40' from a C array */
    NS_Medium_40 = &NS_Medium_40_data;
    /* get font 'NS_Medium_70' from a C array */
    NS_Medium_70 = &NS_Medium_70_data;
    /* get font 'NS_Medium_100' from a C array */
    NS_Medium_100 = &NS_Medium_100_data;
    /* get font 'NS_Medium_140' from a C array */
    NS_Medium_140 = &NS_Medium_140_data;


    /*----------------
     * Images
     *----------------*/
    icon_empty = &icon_empty_data;
    icon_wifi = &icon_wifi_data;
    icon_list = &icon_list_data;
    icon_brightness_full = &icon_brightness_full_data;
    icon_brightness_empty = &icon_brightness_empty_data;
    icon_volume_high = &icon_volume_high_data;
    icon_volume_low = &icon_volume_low_data;
    icon_mute = &icon_mute_data;
    icon_play = &icon_play_data;
    icon_back = &icon_back_data;
    icon_next = &icon_next_data;
    icon_connect = &icon_connect_data;
    icon_vibration = &icon_vibration_data;
    icon_dnd = &icon_dnd_data;
    icon_qr = &icon_qr_data;
    icon_settings_harddisk = &icon_settings_harddisk_data;
    icon_settings_brightness = &icon_settings_brightness_data;
    icon_settings_monitor = &icon_settings_monitor_data;
    icon_settings_information = &icon_settings_information_data;
    icon_settings_smartwatch = &icon_settings_smartwatch_data;
    icon_settings_rotate = &icon_settings_rotate_data;
    icon_settings_power = &icon_settings_power_data;
    icon_settings_bell = &icon_settings_bell_data;
    icon_application = &icon_application_data;
    icon_chat = &icon_chat_data;
    icon_weather = &icon_weather_data;
    icon_gear = &icon_gear_data;
    icon_measurement = &icon_measurement_data;
    icon_stopwatch = &icon_stopwatch_data;
    icon_contacts = &icon_contacts_data;
    icon_navigation = &icon_navigation_data;
    icon_timer = &icon_timer_data;
    icon_music = &icon_music_data;
    icon_folder = &icon_folder_data;
    icon_running = &icon_running_data;
    icon_sleep = &icon_sleep_data;

    /*----------------
     * Global styles
     *----------------*/

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_dark);
        lv_style_set_bg_color(&style_dark, lv_color_hex(0x000000));
        lv_style_set_text_color(&style_dark, lv_color_hex(0xffffff));

        lv_style_init(&style_primary_bg);
        lv_style_set_bg_color(&style_primary_bg, COLOR_PRIMARY);

        lv_style_init(&style_white_bg);
        lv_style_set_bg_color(&style_white_bg, lv_color_hex(0xffffff));

        lv_style_init(&style_icon_recolor);

        lv_style_init(&style_text_small_466);
        lv_style_set_text_font(&style_text_small_466, NS_Medium_20);

        lv_style_init(&style_text_small_360);
        lv_style_set_text_font(&style_text_small_360, NS_Medium_18);

        lv_style_init(&style_text_small_240);
        lv_style_set_text_font(&style_text_small_240, NS_Medium_14);

        lv_style_init(&style_text_normal_466);
        lv_style_set_text_font(&style_text_normal_466, NS_Medium_40);

        lv_style_init(&style_text_normal_360);
        lv_style_set_text_font(&style_text_normal_360, NS_Medium_30);

        lv_style_init(&style_text_normal_240);
        lv_style_set_text_font(&style_text_normal_240, NS_Medium_20);

        lv_style_init(&style_text_large_466);
        lv_style_set_text_font(&style_text_large_466, NS_Medium_140);

        lv_style_init(&style_text_large_360);
        lv_style_set_text_font(&style_text_large_360, NS_Medium_100);

        lv_style_init(&style_text_large_240);
        lv_style_set_text_font(&style_text_large_240, NS_Medium_70);

        style_inited = true;
    }

    /*----------------
     * Subjects
     *----------------*/
    lv_subject_init_int(&sb_screen_size, 0);
    lv_subject_init_int(&sb_screen_type, 0);
    lv_subject_init_int(&sb_app_list_mode, 0);
    lv_subject_set_min_value_int(&sb_app_list_mode, 0);
    lv_subject_set_max_value_int(&sb_app_list_mode, 1);
    lv_subject_init_int(&sb_list_circular_mode, 1);
    lv_subject_set_min_value_int(&sb_list_circular_mode, 0);
    lv_subject_set_max_value_int(&sb_list_circular_mode, 1);
    lv_subject_init_int(&sb_screen_brightness, 80);
    lv_subject_set_min_value_int(&sb_screen_brightness, 1);
    lv_subject_set_max_value_int(&sb_screen_brightness, 100);
    lv_subject_init_int(&sb_screen_rotation, 0);
    lv_subject_set_min_value_int(&sb_screen_rotation, 0);
    lv_subject_set_max_value_int(&sb_screen_rotation, 3);
    lv_subject_init_int(&sb_screen_timeout, 0);
    lv_subject_set_min_value_int(&sb_screen_timeout, 0);
    lv_subject_set_max_value_int(&sb_screen_timeout, 4);
    lv_subject_init_int(&sb_screen_rtw, 1);
    lv_subject_set_min_value_int(&sb_screen_rtw, 0);
    lv_subject_set_max_value_int(&sb_screen_rtw, 1);
    lv_subject_init_int(&sb_battery_percent, 70);
    lv_subject_set_min_value_int(&sb_battery_percent, 0);
    lv_subject_set_max_value_int(&sb_battery_percent, 100);
    lv_subject_init_int(&sb_sound_volume, 40);
    lv_subject_set_min_value_int(&sb_sound_volume, 0);
    lv_subject_set_max_value_int(&sb_sound_volume, 100);
    lv_subject_init_int(&sb_focusable, 1);
    lv_subject_set_min_value_int(&sb_focusable, 0);
    lv_subject_set_max_value_int(&sb_focusable, 1);

    /*----------------
     * Translations
     *----------------*/

#if LV_USE_XML
    /* Register widgets */
    wd_arcoiris_register();
    wd_image_register();
    wd_list_register();

    /* Register fonts */
    lv_xml_register_font(NULL, "NS_Medium_14", NS_Medium_14);
    lv_xml_register_font(NULL, "NS_Medium_16", NS_Medium_16);
    lv_xml_register_font(NULL, "NS_Medium_18", NS_Medium_18);
    lv_xml_register_font(NULL, "NS_Medium_20", NS_Medium_20);
    lv_xml_register_font(NULL, "NS_Medium_30", NS_Medium_30);
    lv_xml_register_font(NULL, "NS_Medium_40", NS_Medium_40);
    lv_xml_register_font(NULL, "NS_Medium_70", NS_Medium_70);
    lv_xml_register_font(NULL, "NS_Medium_100", NS_Medium_100);
    lv_xml_register_font(NULL, "NS_Medium_140", NS_Medium_140);

    /* Register subjects */
    lv_xml_register_subject(NULL, "sb_screen_size", &sb_screen_size);
    lv_xml_register_subject(NULL, "sb_screen_type", &sb_screen_type);
    lv_xml_register_subject(NULL, "sb_app_list_mode", &sb_app_list_mode);
    lv_xml_register_subject(NULL, "sb_list_circular_mode", &sb_list_circular_mode);
    lv_xml_register_subject(NULL, "sb_screen_brightness", &sb_screen_brightness);
    lv_xml_register_subject(NULL, "sb_screen_rotation", &sb_screen_rotation);
    lv_xml_register_subject(NULL, "sb_screen_timeout", &sb_screen_timeout);
    lv_xml_register_subject(NULL, "sb_screen_rtw", &sb_screen_rtw);
    lv_xml_register_subject(NULL, "sb_battery_percent", &sb_battery_percent);
    lv_xml_register_subject(NULL, "sb_sound_volume", &sb_sound_volume);
    lv_xml_register_subject(NULL, "sb_focusable", &sb_focusable);

    /* Register callbacks */
    lv_xml_register_event_cb(NULL, "on_notifications_clicked_cb", on_notifications_clicked_cb);
    lv_xml_register_event_cb(NULL, "on_settings_clicked_cb", on_settings_clicked_cb);
    lv_xml_register_event_cb(NULL, "on_weather_clicked_cb", on_weather_clicked_cb);
    lv_xml_register_event_cb(NULL, "on_simulator_event_cb", on_simulator_event_cb);
#endif

    /* Register all the global assets so that they won't be created again when globals.xml is parsed.
     * While running in the editor skip this step to update the preview when the XML changes */
#if LV_USE_XML && !defined(LV_EDITOR_PREVIEW)
    /* Register images */
    lv_xml_register_image(NULL, "icon_empty", icon_empty);
    lv_xml_register_image(NULL, "icon_wifi", icon_wifi);
    lv_xml_register_image(NULL, "icon_list", icon_list);
    lv_xml_register_image(NULL, "icon_brightness_full", icon_brightness_full);
    lv_xml_register_image(NULL, "icon_brightness_empty", icon_brightness_empty);
    lv_xml_register_image(NULL, "icon_volume_high", icon_volume_high);
    lv_xml_register_image(NULL, "icon_volume_low", icon_volume_low);
    lv_xml_register_image(NULL, "icon_mute", icon_mute);
    lv_xml_register_image(NULL, "icon_play", icon_play);
    lv_xml_register_image(NULL, "icon_back", icon_back);
    lv_xml_register_image(NULL, "icon_next", icon_next);
    lv_xml_register_image(NULL, "icon_connect", icon_connect);
    lv_xml_register_image(NULL, "icon_vibration", icon_vibration);
    lv_xml_register_image(NULL, "icon_dnd", icon_dnd);
    lv_xml_register_image(NULL, "icon_qr", icon_qr);
    lv_xml_register_image(NULL, "icon_settings_harddisk", icon_settings_harddisk);
    lv_xml_register_image(NULL, "icon_settings_brightness", icon_settings_brightness);
    lv_xml_register_image(NULL, "icon_settings_monitor", icon_settings_monitor);
    lv_xml_register_image(NULL, "icon_settings_information", icon_settings_information);
    lv_xml_register_image(NULL, "icon_settings_smartwatch", icon_settings_smartwatch);
    lv_xml_register_image(NULL, "icon_settings_rotate", icon_settings_rotate);
    lv_xml_register_image(NULL, "icon_settings_power", icon_settings_power);
    lv_xml_register_image(NULL, "icon_settings_bell", icon_settings_bell);
    lv_xml_register_image(NULL, "icon_application", icon_application);
    lv_xml_register_image(NULL, "icon_chat", icon_chat);
    lv_xml_register_image(NULL, "icon_weather", icon_weather);
    lv_xml_register_image(NULL, "icon_gear", icon_gear);
    lv_xml_register_image(NULL, "icon_measurement", icon_measurement);
    lv_xml_register_image(NULL, "icon_stopwatch", icon_stopwatch);
    lv_xml_register_image(NULL, "icon_contacts", icon_contacts);
    lv_xml_register_image(NULL, "icon_navigation", icon_navigation);
    lv_xml_register_image(NULL, "icon_timer", icon_timer);
    lv_xml_register_image(NULL, "icon_music", icon_music);
    lv_xml_register_image(NULL, "icon_folder", icon_folder);
    lv_xml_register_image(NULL, "icon_running", icon_running);
    lv_xml_register_image(NULL, "icon_sleep", icon_sleep);
#endif

#if LV_USE_XML == 0
    /*--------------------
     *  Permanent screens
     *-------------------*/
    /* If XML is enabled it's assumed that the permanent screens are created
     * manaully from XML using lv_xml_create() */
#endif
}

/* Callbacks */
#if defined(LV_EDITOR_PREVIEW)
void __attribute__((weak)) on_notifications_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("on_notifications_clicked_cb was called\n");
}
void __attribute__((weak)) on_settings_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("on_settings_clicked_cb was called\n");
}
void __attribute__((weak)) on_weather_clicked_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("on_weather_clicked_cb was called\n");
}
void __attribute__((weak)) on_simulator_event_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    LV_LOG("on_simulator_event_cb was called\n");
}
#endif

/**********************
 *   STATIC FUNCTIONS
 **********************/