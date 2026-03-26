/**
 * @file notification_item_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "notification_item_gen.h"
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

lv_obj_t * notification_item_create(lv_obj_t * parent, const void * icon, const char * title, const char * time, const char * message)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_base;
    static lv_style_t style_base_360;
    static lv_style_t style_base_240;
    static lv_style_t style_title_cont;
    static lv_style_t style_text_cont;
    static lv_style_t style_text;
    static lv_style_t style_pressed;
    static lv_style_t style_focused;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_base);
        lv_style_set_width(&style_base, lv_pct(100));
        lv_style_set_height(&style_base, 104);
        lv_style_set_text_font(&style_base, NS_Medium_30);
        lv_style_set_text_color(&style_base, lv_color_hex3(0xfff));
        lv_style_set_radius(&style_base, 30);
        lv_style_set_bg_color(&style_base, lv_color_hex(0xb7b7b7));
        lv_style_set_bg_opa(&style_base, 20);
        lv_style_set_layout(&style_base, LV_LAYOUT_FLEX);
        lv_style_set_flex_flow(&style_base, LV_FLEX_FLOW_COLUMN);
        lv_style_set_pad_all(&style_base, 10);
        lv_style_set_pad_row(&style_base, 5);

        lv_style_init(&style_base_360);
        lv_style_set_height(&style_base_360, 86);
        lv_style_set_radius(&style_base_360, 25);
        lv_style_set_pad_all(&style_base_360, 8);
        lv_style_set_pad_row(&style_base_360, 3);

        lv_style_init(&style_base_240);
        lv_style_set_height(&style_base_240, 64);
        lv_style_set_radius(&style_base_240, 20);
        lv_style_set_pad_all(&style_base_240, 6);
        lv_style_set_pad_row(&style_base_240, 0);

        lv_style_init(&style_title_cont);
        lv_style_set_width(&style_title_cont, lv_pct(100));
        lv_style_set_height(&style_title_cont, LV_SIZE_CONTENT);
        lv_style_set_layout(&style_title_cont, LV_LAYOUT_FLEX);
        lv_style_set_pad_column(&style_title_cont, 10);
        lv_style_set_pad_hor(&style_title_cont, 5);

        lv_style_init(&style_text_cont);
        lv_style_set_flex_grow(&style_text_cont, 1);
        lv_style_set_height(&style_text_cont, LV_SIZE_CONTENT);
        lv_style_set_layout(&style_text_cont, LV_LAYOUT_FLEX);
        lv_style_set_flex_flow(&style_text_cont, LV_FLEX_FLOW_COLUMN);
        lv_style_set_pad_top(&style_text_cont, 0);
        lv_style_set_pad_row(&style_text_cont, 0);

        lv_style_init(&style_text);
        lv_style_set_width(&style_text, lv_pct(100));
        lv_style_set_pad_all(&style_text, 5);

        lv_style_init(&style_pressed);
        lv_style_set_bg_color(&style_pressed, lv_color_hex(0xffffff));
        lv_style_set_bg_opa(&style_pressed, 127);

        lv_style_init(&style_focused);
        lv_style_set_height(&style_focused, LV_SIZE_CONTENT);
        lv_style_set_bg_opa(&style_focused, 40);

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(parent);
    lv_obj_set_name_static(lv_obj_0, "notification_item_#");
    lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLL_ON_FOCUS, true);

    lv_obj_remove_style_all(lv_obj_0);
    lv_obj_add_style(lv_obj_0, &style_base, 0);
    lv_obj_add_style(lv_obj_0, &style_focused, LV_STATE_FOCUSED);
    lv_obj_bind_style(lv_obj_0, &style_base_360, 0, &sb_screen_size, 1);
    lv_obj_bind_style(lv_obj_0, &style_base_240, 0, &sb_screen_size, 2);
    lv_obj_bind_style(lv_obj_0, &style_focused, 0, &sb_focusable, 1);
    lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
    lv_obj_set_flag(lv_obj_1, LV_OBJ_FLAG_CLICKABLE, false);
    lv_obj_remove_style_all(lv_obj_1);
    lv_obj_add_style(lv_obj_1, &style_title_cont, 0);
    lv_obj_t * wd_image_0 = wd_image_create(lv_obj_1);
    wd_image_set_src(wd_image_0, icon);
    wd_image_set_scale_0(wd_image_0, 256);
    wd_image_set_scale_1(wd_image_0, 200);
    wd_image_set_scale_2(wd_image_0, 140);
    wd_image_set_size_1(wd_image_0, 50);
    wd_image_set_size_2(wd_image_0, 35);
    wd_image_bind_scale(wd_image_0, &sb_screen_size);
    
    lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_1);
    lv_obj_set_flag(lv_obj_2, LV_OBJ_FLAG_CLICKABLE, false);
    lv_obj_remove_style_all(lv_obj_2);
    lv_obj_add_style(lv_obj_2, &style_text_cont, 0);
    lv_obj_t * lv_label_0 = lv_label_create(lv_obj_2);
    lv_label_set_text(lv_label_0, title);
    lv_obj_set_width(lv_label_0, lv_pct(100));
    lv_obj_bind_style(lv_label_0, &style_text_normal_466, 0, &sb_screen_size, 0);
    lv_obj_bind_style(lv_label_0, &style_text_normal_360, 0, &sb_screen_size, 1);
    lv_obj_bind_style(lv_label_0, &style_text_normal_240, 0, &sb_screen_size, 2);
    
    lv_obj_t * lv_label_1 = lv_label_create(lv_obj_2);
    lv_label_set_text(lv_label_1, time);
    lv_obj_set_width(lv_label_1, lv_pct(100));
    lv_obj_bind_style(lv_label_1, &style_text_small_466, 0, &sb_screen_size, 0);
    lv_obj_bind_style(lv_label_1, &style_text_small_360, 0, &sb_screen_size, 1);
    lv_obj_bind_style(lv_label_1, &style_text_small_240, 0, &sb_screen_size, 2);
    
    lv_obj_t * lv_label_2 = lv_label_create(lv_obj_0);
    lv_label_set_text(lv_label_2, message);
    lv_obj_add_style(lv_label_2, &style_text, 0);
    lv_obj_bind_style(lv_label_2, &style_text_small_466, 0, &sb_screen_size, 0);
    lv_obj_bind_style(lv_label_2, &style_text_small_360, 0, &sb_screen_size, 1);
    lv_obj_bind_style(lv_label_2, &style_text_small_240, 0, &sb_screen_size, 2);

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

