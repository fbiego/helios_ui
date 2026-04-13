/**
 * @file hs_text_icon_normal_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "hs_text_icon_normal_gen.h"
#include "../../../../helios_ui.h"

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

lv_obj_t * hs_text_icon_normal_create(lv_obj_t * parent, const void * icon, const char * text, const char * tag)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_base;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_base);
        lv_style_set_width(&style_base, LV_SIZE_CONTENT);
        lv_style_set_height(&style_base, LV_SIZE_CONTENT);
        lv_style_set_layout(&style_base, LV_LAYOUT_FLEX);
        lv_style_set_flex_track_place(&style_base, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_cross_place(&style_base, LV_FLEX_ALIGN_CENTER);
        lv_style_set_pad_column(&style_base, 5);

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(parent);
    lv_obj_set_name_static(lv_obj_0, "hs_text_icon_normal_#");

    lv_obj_remove_style_all(lv_obj_0);
    lv_obj_add_style(lv_obj_0, &style_base, 0);
    lv_obj_t * wd_image_0 = wd_image_create(lv_obj_0);
    wd_image_set_src(wd_image_0, icon);
    wd_image_set_scale_1(wd_image_0, 240);
    wd_image_set_scale_2(wd_image_0, 160);
    wd_image_set_size_1(wd_image_0, 30);
    wd_image_set_size_2(wd_image_0, 18);
    wd_image_bind_scale(wd_image_0, &sb_screen_size);
    
    lv_obj_t * hs_text_normal_0 = hs_text_normal_create(lv_obj_0);
    lv_label_set_text(hs_text_normal_0, text);
    lv_label_set_translation_tag(hs_text_normal_0, tag);
    lv_obj_set_style_pad_top(hs_text_normal_0, 5, 0);

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

