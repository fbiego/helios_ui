/**
 * @file watchface_default_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "watchface_default_gen.h"
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

lv_obj_t * watchface_default_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_base;
    static lv_style_t style_column;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_base);
        lv_style_set_width(&style_base, lv_pct(100));
        lv_style_set_height(&style_base, lv_pct(100));
        lv_style_set_bg_color(&style_base, lv_color_hex(0x6688ee));
        lv_style_set_text_color(&style_base, lv_color_hex3(0xfff));

        lv_style_init(&style_column);
        lv_style_set_width(&style_column, lv_pct(100));
        lv_style_set_height(&style_column, lv_pct(100));
        lv_style_set_layout(&style_column, LV_LAYOUT_FLEX);
        lv_style_set_flex_flow(&style_column, LV_FLEX_FLOW_COLUMN);
        lv_style_set_flex_main_place(&style_column, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_track_place(&style_column, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_cross_place(&style_column, LV_FLEX_ALIGN_CENTER);

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(parent);
    lv_obj_set_name_static(lv_obj_0, "watchface_default_#");
    lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_CLICKABLE, false);

    lv_obj_remove_style_all(lv_obj_0);
    lv_obj_add_style(lv_obj_0, &style_base, 0);
    lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
    lv_obj_set_flag(lv_obj_1, LV_OBJ_FLAG_CLICKABLE, false);
    lv_obj_remove_style_all(lv_obj_1);
    lv_obj_add_style(lv_obj_1, &style_column, 0);
    lv_obj_t * hs_text_large_0 = hs_text_large_create(lv_obj_1);
    lv_label_set_text(hs_text_large_0, "12:05");
    lv_obj_set_y(hs_text_large_0, -50);
    lv_obj_set_align(hs_text_large_0, LV_ALIGN_CENTER);
    
    lv_obj_t * hs_text_normal_0 = hs_text_normal_create(lv_obj_1);
    lv_label_set_translation_tag(hs_text_normal_0, "mon");
    
    lv_obj_t * hs_row_0 = hs_row_create(lv_obj_1);
    lv_obj_set_width(hs_row_0, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_column(hs_row_0, 10, 0);
    lv_obj_t * hs_text_normal_1 = hs_text_normal_create(hs_row_0);
    lv_label_set_text(hs_text_normal_1, "13");
    
    lv_obj_t * hs_text_normal_2 = hs_text_normal_create(hs_row_0);
    lv_label_set_translation_tag(hs_text_normal_2, "apr");

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

