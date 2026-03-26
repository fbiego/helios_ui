/**
 * @file boot_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "boot_gen.h"
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

lv_obj_t * boot_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    static bool style_inited = false;

    if (!style_inited) {

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
    lv_obj_set_name_static(lv_obj_0, "boot_#");

    lv_obj_add_style(lv_obj_0, &style_dark, 0);
    lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
    lv_label_set_text(lv_label_0, "HELIOS");
    lv_obj_set_align(lv_label_0, LV_ALIGN_CENTER);
    lv_obj_bind_style(lv_label_0, &style_text_normal_466, 0, &sb_screen_size, 0);
    lv_obj_bind_style(lv_label_0, &style_text_normal_360, 0, &sb_screen_size, 1);
    lv_obj_bind_style(lv_label_0, &style_text_normal_240, 0, &sb_screen_size, 2);

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

