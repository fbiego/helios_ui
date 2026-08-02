/**
 * @file main.c
 *
 * Emscripten entry point for a UI exported from LVGL Pro.
 */

#ifdef LVGL_PRO_WEB_BUILD

#include <stdlib.h>

#include <emscripten.h>
#include "lvgl.h"
#include UI_HEADER

static void web_hal_init(int32_t hor_res, int32_t ver_res);
static void web_loop(void);

int main(int argc, char ** argv)
{
    int32_t hor_res = UI_WIDTH;
    int32_t ver_res = UI_HEIGHT;

    if(argc >= 3) {
        hor_res = (int32_t)atoi(argv[1]);
        ver_res = (int32_t)atoi(argv[2]);
    }

    lv_init();
    web_hal_init(hor_res, ver_res);
    UI_INIT("");

    emscripten_set_main_loop(web_loop, 0, 1);
    return 0;
}

static void web_loop(void)
{
    lv_timer_handler();
}

static void web_hal_init(int32_t hor_res, int32_t ver_res)
{
    lv_display_t * disp = lv_sdl_window_create(hor_res, ver_res);
    (void)disp;

    lv_group_t * group = lv_group_create();
    lv_group_set_default(group);

    lv_indev_t * mouse = lv_sdl_mouse_create();
    lv_indev_set_group(mouse, group);

    lv_indev_t * mousewheel = lv_sdl_mousewheel_create();
    lv_indev_set_group(mousewheel, group);

    lv_indev_t * keyboard = lv_sdl_keyboard_create();
    lv_indev_set_group(keyboard, group);
}

#endif /*LVGL_PRO_WEB_BUILD*/
