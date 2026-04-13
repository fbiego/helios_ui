/**
 * @file settings_about_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "settings_about_gen.h"
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

lv_obj_t * settings_about_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_base;
    static lv_style_t style_pad_360;
    static lv_style_t style_pad_240;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_base);
        lv_style_set_pad_row(&style_base, 10);
        lv_style_set_pad_ver(&style_base, 150);

        lv_style_init(&style_pad_360);
        lv_style_set_pad_ver(&style_pad_360, 90);
        lv_style_set_pad_hor(&style_pad_360, 30);

        lv_style_init(&style_pad_240);
        lv_style_set_pad_ver(&style_pad_240, 60);
        lv_style_set_pad_hor(&style_pad_240, 20);

        style_inited = true;
    }

    lv_obj_t * wd_list_0 = wd_list_create(parent);
    lv_obj_set_name_static(wd_list_0, "settings_about_#");
    wd_list_bind_screen(wd_list_0, &sb_screen_size);

    lv_obj_t * wd_list_container_0 = wd_list_get_container(wd_list_0);
    lv_obj_add_style(wd_list_container_0, &style_base, 0);
    lv_obj_bind_style(wd_list_container_0, &style_pad_360, 0, &sb_screen_size, 1);
    lv_obj_bind_style(wd_list_container_0, &style_pad_240, 0, &sb_screen_size, 2);
    lv_obj_t * hs_card_0 = hs_card_create(wd_list_container_0);
    hs_info_create(hs_card_0, "Viewe Smart Ring", "", "");
    
    hs_line_create(hs_card_0);
    
    hs_info_create(hs_card_0, "ESP32 S3", "", "34:54:56:23:43:32");
    
    hs_line_create(hs_card_0);
    
    hs_info_create(hs_card_0, "RAM", "", "384KB");
    
    hs_info_create(hs_card_0, "PSRAM", "", "8MB");
    
    hs_line_create(hs_card_0);
    
    hs_info_create(hs_card_0, "Flash", "", "16MB");
    
    hs_line_create(hs_card_0);
    
    hs_info_create(hs_card_0, "Label", "display", "466x466");
    
    hs_line_create(hs_card_0);
    
    hs_info_create(hs_card_0, "Label", "firmware", "v1.3");
    
    lv_obj_t * hs_card_1 = hs_card_create(wd_list_container_0);
    hs_info_create(hs_card_1, "Helios UI", "", "v0.1");
    
    hs_info_create(hs_card_1, "LVGL", "", "v9.4.0");

    LV_TRACE_OBJ_CREATE("finished");

    return wd_list_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

