/**
 * @file control_group_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "control_group_gen.h"
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

lv_obj_t * control_group_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_group;
    static lv_style_t style_group_360;
    static lv_style_t style_group_240;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_group);
        lv_style_set_width(&style_group, 360);
        lv_style_set_height(&style_group, LV_SIZE_CONTENT);
        lv_style_set_radius(&style_group, 55);
        lv_style_set_layout(&style_group, LV_LAYOUT_FLEX);
        lv_style_set_flex_flow(&style_group, LV_FLEX_FLOW_ROW_WRAP);
        lv_style_set_pad_row(&style_group, 15);
        lv_style_set_pad_column(&style_group, 15);

        lv_style_init(&style_group_360);
        lv_style_set_width(&style_group_360, 290);
        lv_style_set_pad_row(&style_group_360, 10);
        lv_style_set_pad_column(&style_group_360, 10);

        lv_style_init(&style_group_240);
        lv_style_set_width(&style_group_240, 200);
        lv_style_set_pad_row(&style_group_240, 10);
        lv_style_set_pad_column(&style_group_240, 10);

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(parent);
    lv_obj_set_name_static(lv_obj_0, "control_group_#");
    lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_EVENT_BUBBLE, true);

    lv_obj_remove_style_all(lv_obj_0);
    lv_obj_add_style(lv_obj_0, &style_group, 0);
    lv_obj_bind_style(lv_obj_0, &style_group_360, 0, &sb_screen_size, 1);
    lv_obj_bind_style(lv_obj_0, &style_group_240, 0, &sb_screen_size, 2);

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

