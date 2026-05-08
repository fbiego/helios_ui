/**
 * @file screens.h
 *
 */

#ifndef SCREENS_H
#define SCREENS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
    #include "lvgl_private.h"
#else
    #include "lvgl/lvgl.h"
    #include "lvgl/lvgl_private.h"
#endif

#include "../helios_ui_gen.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    lv_obj_t * (*screen_fn)(void);   // function that returns screen object
    lv_scr_load_anim_t anim;         // animation to use
} gesture_action_t;

typedef struct {
    gesture_action_t left;
    gesture_action_t right;
    gesture_action_t up;
    gesture_action_t down;
} gesture_map_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t * screen_home(void);

lv_obj_t * screen_applications(void);

lv_obj_t * screen_notifications(void);

lv_obj_t * screen_settings(void);

lv_obj_t * screen_widgets(void);

lv_obj_t * screen_weather(void);

lv_obj_t * screen_contacts(void);

lv_obj_t * screen_navigation(void);


lv_obj_t * get_list_from_wd(lv_obj_t * parent, const char * name);

/**********************
 *      MACROS
 **********************/

#define CC_SCREENS_USER_DATA

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*SCREENS_H*/