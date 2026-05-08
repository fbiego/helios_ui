/**
 * @file contacts_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "contacts_gen.h"
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

lv_obj_t * contacts_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_list;
    static lv_style_t style_cont;
    static lv_style_t style_cont_360;
    static lv_style_t style_cont_240;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_list);
        lv_style_set_bg_color(&style_list, lv_color_hex(0x000000));
        lv_style_set_bg_opa(&style_list, 255);

        lv_style_init(&style_cont);
        lv_style_set_pad_top(&style_cont, 120);
        lv_style_set_pad_bottom(&style_cont, 150);
        lv_style_set_pad_hor(&style_cont, 33);
        lv_style_set_flex_flow(&style_cont, LV_FLEX_FLOW_COLUMN_REVERSE);

        lv_style_init(&style_cont_360);
        lv_style_set_pad_hor(&style_cont_360, 30);
        lv_style_set_pad_top(&style_cont_360, 80);
        lv_style_set_pad_bottom(&style_cont_360, 100);

        lv_style_init(&style_cont_240);
        lv_style_set_pad_hor(&style_cont_240, 20);
        lv_style_set_pad_row(&style_cont_240, 5);
        lv_style_set_pad_top(&style_cont_240, 60);
        lv_style_set_pad_bottom(&style_cont_240, 80);

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
    lv_obj_set_name_static(lv_obj_0, "contacts_#");

    lv_obj_add_style(lv_obj_0, &style_dark, 0);
    lv_obj_t * hs_text_small_0 = hs_text_small_create(lv_obj_0);
    lv_obj_set_width(hs_text_small_0, lv_pct(60));
    lv_label_set_text(hs_text_small_0, "No contacts avaialble, please sync using Chronos app");
    lv_obj_set_style_text_align(hs_text_small_0, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_align(hs_text_small_0, LV_ALIGN_CENTER);
    
    lv_obj_t * contacts_list = wd_list_create(lv_obj_0);
    lv_obj_set_name(contacts_list, "contacts_list");
    wd_list_bind_circular(contacts_list, &sb_list_circular_mode);
    wd_list_bind_screen(contacts_list, &sb_screen_size);
    lv_obj_add_style(contacts_list, &style_list, 0);
    lv_obj_t * wd_list_container_0 = wd_list_get_container(contacts_list);
    lv_obj_add_style(wd_list_container_0, &style_cont, 0);
    lv_obj_bind_style(wd_list_container_0, &style_cont_360, 0, &sb_screen_size, 1);
    lv_obj_bind_style(wd_list_container_0, &style_cont_240, 0, &sb_screen_size, 2);
    contact_item_create(wd_list_container_0, "John Doe", "03244875324");
    
    contact_item_create(wd_list_container_0, "John Doe", "03244875324");
    
    lv_obj_t * contact_item_2 = contact_item_create(wd_list_container_0, "John Doe", "03244875324");
    lv_obj_set_style_bg_color(contact_item_2, lv_color_hex(0x0f4010), 0);
    
    contact_item_create(wd_list_container_0, "John Doe", "03244875324");
    
    contact_item_create(wd_list_container_0, "John Doe", "03244875324");

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

