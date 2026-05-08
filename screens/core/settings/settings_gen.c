/**
 * @file settings_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "settings_gen.h"
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

lv_obj_t * settings_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_cont;
    static lv_style_t style_cont_360;
    static lv_style_t style_cont_240;
    static lv_style_t style_flex;
    static lv_style_t style_pad_grid;
    static lv_style_t style_pad_grid_360;
    static lv_style_t style_pad_grid_240;
    static lv_style_t style_pad_grid_410;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_cont);
        lv_style_set_width(&style_cont, 466);
        lv_style_set_height(&style_cont, 466);
        lv_style_set_align(&style_cont, LV_ALIGN_CENTER);
        lv_style_set_border_width(&style_cont, 0);
        lv_style_set_pad_top(&style_cont, 100);
        lv_style_set_pad_bottom(&style_cont, 150);
        lv_style_set_pad_hor(&style_cont, 33);

        lv_style_init(&style_cont_360);
        lv_style_set_pad_hor(&style_cont_360, 30);
        lv_style_set_pad_top(&style_cont_360, 80);
        lv_style_set_pad_bottom(&style_cont_360, 100);

        lv_style_init(&style_cont_240);
        lv_style_set_pad_hor(&style_cont_240, 20);
        lv_style_set_pad_row(&style_cont_240, 5);
        lv_style_set_pad_top(&style_cont_240, 60);
        lv_style_set_pad_bottom(&style_cont_240, 80);

        lv_style_init(&style_flex);
        lv_style_set_layout(&style_flex, LV_LAYOUT_FLEX);
        lv_style_set_flex_flow(&style_flex, LV_FLEX_FLOW_ROW_WRAP);
        lv_style_set_pad_column(&style_flex, 15);
        lv_style_set_pad_row(&style_flex, 10);

        lv_style_init(&style_pad_grid);
        lv_style_set_pad_hor(&style_pad_grid, 53);
        lv_style_set_pad_row(&style_pad_grid, 15);

        lv_style_init(&style_pad_grid_360);
        lv_style_set_pad_hor(&style_pad_grid_360, 33);
        lv_style_set_pad_row(&style_pad_grid_360, 10);
        lv_style_set_pad_column(&style_pad_grid_360, 12);

        lv_style_init(&style_pad_grid_240);
        lv_style_set_pad_hor(&style_pad_grid_240, 20);
        lv_style_set_pad_row(&style_pad_grid_240, 10);
        lv_style_set_pad_column(&style_pad_grid_240, 10);

        lv_style_init(&style_pad_grid_410);
        lv_style_set_pad_hor(&style_pad_grid_410, 25);

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
    lv_obj_set_name_static(lv_obj_0, "settings_#");

    lv_obj_add_style(lv_obj_0, &style_dark, 0);
    lv_obj_t * main_settings_list = wd_list_create(lv_obj_0);
    lv_obj_set_name(main_settings_list, "main_settings_list");
    wd_list_bind_mode(main_settings_list, &sb_app_list_mode);
    wd_list_bind_circular(main_settings_list, &sb_list_circular_mode);
    wd_list_bind_screen(main_settings_list, &sb_screen_size);
    lv_obj_t * wd_list_container_0 = wd_list_get_container(main_settings_list);
    lv_obj_bind_state_if_eq(wd_list_container_0, &sb_app_list_mode, LV_STATE_USER_1, 1);
    lv_obj_bind_style(wd_list_container_0, &style_cont_360, 0, &sb_screen_size, 1);
    lv_obj_bind_style(wd_list_container_0, &style_cont_240, 0, &sb_screen_size, 2);
    lv_obj_bind_style(wd_list_container_0, &style_pad_grid, LV_STATE_USER_1, &sb_screen_size, 0);
    lv_obj_bind_style(wd_list_container_0, &style_pad_grid_360, LV_STATE_USER_1, &sb_screen_size, 1);
    lv_obj_bind_style(wd_list_container_0, &style_pad_grid_240, LV_STATE_USER_1, &sb_screen_size, 2);
    lv_obj_bind_style(wd_list_container_0, &style_pad_grid_410, LV_STATE_USER_1, &sb_screen_width, 410);
    app_item_create(wd_list_container_0, icon_settings_monitor, "Display", "display");
    
    app_item_create(wd_list_container_0, icon_settings_smartwatch, "System", "system");
    
    app_item_create(wd_list_container_0, icon_settings_bell, "Alerts", "alerts");
    
    app_item_create(wd_list_container_0, icon_settings_power, "Battery", "battery");
    
    app_item_create(wd_list_container_0, icon_settings_harddisk, "Storage", "storage");
    
    app_item_create(wd_list_container_0, icon_settings_information, "About", "about");

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

