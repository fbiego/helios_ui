/**
 * @file wd_list_gen.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "wd_list_private_gen.h"
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
    #include "lvgl_private.h"
#else
    #include "lvgl/lvgl.h"
    #include "lvgl/lvgl_private.h"
#endif
#include "../../helios_ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  GLOBAL PROTOTYPES
 **********************/

void wd_list_constructor_hook(lv_obj_t * obj);
void wd_list_destructor_hook(lv_obj_t * obj);
void wd_list_event_hook(lv_event_t * e);

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void wd_list_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void wd_list_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void wd_list_event(const lv_obj_class_t * class_p, lv_event_t * e);

/**********************
 *  STATIC VARIABLES
 **********************/

const lv_obj_class_t wd_list_class = {
    .base_class = &lv_obj_class,
    .constructor_cb = wd_list_constructor,
    .destructor_cb = wd_list_destructor,
    .event_cb = wd_list_event,
    .instance_size = sizeof(wd_list_t),
    .editable = 1,
    .name = "wd_list"
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * wd_list_create(lv_obj_t * parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(&wd_list_class, parent);
    lv_obj_class_init_obj(obj);

    return obj;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void wd_list_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");

    wd_list_t * widget = (wd_list_t *)obj;
    static lv_style_t style_cont;
    static lv_style_t style_flex;
    static lv_style_t style_pad_grid;
    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_cont);
        lv_style_set_width(&style_cont, lv_pct(100));
        lv_style_set_height(&style_cont, lv_pct(100));
        lv_style_set_align(&style_cont, LV_ALIGN_CENTER);
        lv_style_set_border_width(&style_cont, 0);
        lv_style_set_pad_top(&style_cont, 100);
        lv_style_set_pad_bottom(&style_cont, 150);
        lv_style_set_pad_hor(&style_cont, 33);

        lv_style_init(&style_flex);
        lv_style_set_layout(&style_flex, LV_LAYOUT_FLEX);
        lv_style_set_flex_flow(&style_flex, LV_FLEX_FLOW_ROW_WRAP);
        lv_style_set_pad_column(&style_flex, 15);
        lv_style_set_pad_row(&style_flex, 10);

        lv_style_init(&style_pad_grid);
        lv_style_set_pad_hor(&style_pad_grid, 53);
        lv_style_set_pad_row(&style_pad_grid, 15);

        style_inited = true;
    }
    lv_obj_set_width(obj, lv_pct(100));
    lv_obj_set_height(obj, lv_pct(100));

    lv_obj_t * list = lv_obj_create(obj);
    lv_obj_set_name(list, "list");
    widget->list = list;
    lv_obj_remove_style_all(list);
    lv_obj_add_style(list, &style_cont, 0);
    lv_obj_add_style(list, &style_flex, 0);


    wd_list_constructor_hook(obj);

    LV_TRACE_OBJ_CREATE("finished");
}

static void wd_list_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);

    wd_list_destructor_hook(obj);
}

static void wd_list_event(const lv_obj_class_t * class_p, lv_event_t * e)
{
    LV_UNUSED(class_p);

    lv_result_t res;

    /* Call the ancestor's event handler */
    res = lv_obj_event_base(&wd_list_class, e);
    if(res != LV_RESULT_OK) return;

    wd_list_event_hook(e);
}

