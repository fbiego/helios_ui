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
static void web_memory_monitor_init(void);
static void web_memory_monitor_update(void);
static void web_screen_event_cb(lv_event_t * e);
static void web_publish_screen_name(const lv_obj_t * screen);

EM_JS(void, web_memory_monitor_set_available, (int available), {
    if (typeof window !== "undefined" && typeof window.setLvglMemoryMonitorAvailable === "function") {
        window.setLvglMemoryMonitorAvailable(!!available);
    }
});

EM_JS(void, web_screen_name_publish, (const char * screen_name), {
    if (typeof window !== "undefined" && typeof window.onLvglScreenName === "function") {
        window.onLvglScreenName(screen_name ? UTF8ToString(screen_name) : null);
    }
});

#if LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN
EM_JS(void, web_memory_monitor_publish, (double total_size,
                                         double free_size,
                                         double free_biggest_size,
                                         double used_count,
                                         double free_count,
                                         double max_used,
                                         int used_pct,
                                         int frag_pct), {
    if (typeof window !== "undefined" && typeof window.onLvglMemoryStats === "function") {
        window.onLvglMemoryStats({
            totalSize: total_size,
            freeSize: free_size,
            freeBiggestSize: free_biggest_size,
            usedCount: used_count,
            freeCount: free_count,
            maxUsed: max_used,
            usedPct: used_pct,
            fragPct: frag_pct
        });
    }
});
#endif

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
    web_memory_monitor_init();
    web_publish_screen_name(lv_screen_active());

    emscripten_set_main_loop(web_loop, 0, 1);
    return 0;
}

static void web_loop(void)
{
    lv_timer_handler();
    web_memory_monitor_update();
}

static void web_memory_monitor_init(void)
{
#if LV_USE_SYSMON
#if LV_USE_MEM_MONITOR
    lv_sysmon_hide_memory(NULL);
#endif
#if LV_USE_PERF_MONITOR
    lv_sysmon_hide_performance(NULL);
#endif
#endif

#if LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN
    web_memory_monitor_set_available(1);
#else
    web_memory_monitor_set_available(0);
#endif
}

static void web_memory_monitor_update(void)
{
#if LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN
    static uint32_t last_update_ms;
    const uint32_t interval_ms = 500;

    if(last_update_ms != 0 && lv_tick_elaps(last_update_ms) < interval_ms) return;
    last_update_ms = lv_tick_get();

    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
    web_publish_screen_name(lv_screen_active());
    web_memory_monitor_publish((double)mon.total_size,
                               (double)mon.free_size,
                               (double)mon.free_biggest_size,
                               (double)mon.used_cnt,
                               (double)mon.free_cnt,
                               (double)mon.max_used,
                               mon.used_pct,
                               mon.frag_pct);
#endif
}

static void web_screen_event_cb(lv_event_t * e)
{
    lv_obj_t * screen = lv_event_get_param(e);
    if(screen == NULL) screen = lv_screen_active();
    web_publish_screen_name(screen);
}

static void web_publish_screen_name(const lv_obj_t * screen)
{
    const char * name = screen ? lv_obj_get_name(screen) : NULL;
    web_screen_name_publish(name);
}

static void web_hal_init(int32_t hor_res, int32_t ver_res)
{
    lv_display_t * disp = lv_sdl_window_create(hor_res, ver_res);
    lv_display_add_event_cb(disp, web_screen_event_cb, LV_EVENT_SCREEN_LOADED, NULL);

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
