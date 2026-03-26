/**
 * @file helios_ui.h
 */

#ifndef HELIOS_UI_H
#define HELIOS_UI_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "helios_ui_gen.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the component library
 */
void helios_ui_init(const char * asset_path);

void uart_log(const char *format, ...);

lv_obj_t * screen_home(void);

lv_obj_t * screen_applications(void);

lv_obj_t * screen_notifications(void);

lv_obj_t * screen_widgets(void);

int32_t get_screen_width(int32_t index);

void set_screen(int32_t w, int32_t h);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*HELIOS_UI_H*/