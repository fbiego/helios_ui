/**
 * @file settings_display_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "settings_display_gen.h"
#include "../../../helios_ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * settings_display_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_base;
    static lv_style_t style_pad_360;
    static lv_style_t style_pad_240;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_base);
        lv_style_set_pad_row(&style_base, 10);
        lv_style_set_pad_ver(&style_base, 120);

        lv_style_init(&style_pad_360);
        lv_style_set_pad_ver(&style_pad_360, 90);
        lv_style_set_pad_hor(&style_pad_360, 25);

        lv_style_init(&style_pad_240);
        lv_style_set_pad_ver(&style_pad_240, 60);
        lv_style_set_pad_hor(&style_pad_240, 20);

        style_inited = true;
    }

    lv_obj_t * wd_list_0 = wd_list_create(parent);
    lv_obj_set_name_static(wd_list_0, "settings_display_#");
    wd_list_bind_screen(wd_list_0, &sb_screen_size);

    lv_obj_t * wd_list_container_0 = wd_list_get_container(wd_list_0);
    lv_obj_add_style(wd_list_container_0, &style_base, 0);
    lv_obj_bind_style(wd_list_container_0, &style_pad_360, 0, &sb_screen_size, 1);
    lv_obj_bind_style(wd_list_container_0, &style_pad_240, 0, &sb_screen_size, 2);
    lv_obj_t * hs_card_0 = hs_card_create(wd_list_container_0);
    lv_obj_set_style_pad_ver(hs_card_0, 5, 0);
    hs_slider_create(hs_card_0, "Brightness", &sb_screen_brightness);
    
    hs_line_create(hs_card_0);
    
    hs_dropdown_create(hs_card_0, "Timeout", &sb_screen_timeout, "5 seconds\n10 seconds\n20 seconds\n30 seconds\nAlways on");
    
    lv_obj_t * hs_card_1 = hs_card_create(wd_list_container_0);
    lv_obj_set_style_pad_top(hs_card_1, 5, 0);
    hs_dropdown_create(hs_card_1, "Rotation", &sb_screen_rotation, "Default\n90\n180\n270");
    
    hs_line_create(hs_card_1);
    
    hs_switch_create(hs_card_1, "Raise to wake", &sb_list_circular_mode);

    LV_TRACE_OBJ_CREATE("finished");

    return wd_list_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

