/**
 * @file helios_ui.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "helios_ui.h"

/*********************
 *      DEFINES
 *********************/

#define LANG_TAG_COUNT (sizeof(lang_tags) / sizeof(lang_tags[0]))


/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    int32_t parent_width;
    int32_t child1_width;
    int32_t child1_height;
    int32_t child2_width;
    bool overflow;
} hs_info_layout_state_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void on_language_change(lv_event_t * e);
static void language_observer_cb(lv_observer_t *observer, lv_subject_t *subject);

static void screen_res_cb(lv_event_t *e);

static const char * lang_tag_get_by_index(int index);
static int lang_tag_get_index(const char * str, int def);


/**********************
 *  STATIC VARIABLES
 **********************/
static const char * lang_tags[] = {
    "en", "pt", "de", "es", "fr", "hu", "ru", "el", "th", "zh", "ja", "hi"
};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void helios_ui_init(const char * asset_path)
{
    helios_ui_init_gen(asset_path);


    /* Add your own custom code here if needed */

    lv_obj_add_event_cb(lv_screen_active(), on_language_change, LV_EVENT_TRANSLATION_LANGUAGE_CHANGED, NULL);

    lv_subject_add_observer(&sb_language, language_observer_cb, NULL);
    
#if defined(LV_EDITOR_PREVIEW)
    lv_display_t *disp = lv_display_get_default();
    if (disp) {
        lv_display_add_event_cb(disp, screen_res_cb, LV_EVENT_RESOLUTION_CHANGED, NULL);
        lv_display_send_event(disp, LV_EVENT_RESOLUTION_CHANGED, NULL);
    }
#endif

    char buf[32];
    lv_snprintf(buf, sizeof(buf), "v%d.%d.%d", LVGL_VERSION_MAJOR, LVGL_VERSION_MINOR, LVGL_VERSION_PATCH);
    lv_subject_copy_string(&sb_lvgl_version, buf);

}


int32_t get_screen_width(int32_t index)
{
    switch (index)
    {
        case 0: return 466;
        case 1: return 360;
        case 2: return 240;
    }
    return 466;

}

void on_settings_clicked_cb(lv_event_t * e)
{
    lv_screen_load_anim(screen_settings(), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}

void on_weather_clicked_cb(lv_event_t * e)
{
    lv_screen_load_anim(screen_weather(), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}

void on_notifications_clicked_cb(lv_event_t * e)
{
    notifications_to_apps = true;
    lv_screen_load_anim(screen_notifications(), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}

void on_contacts_clicked_cb(lv_event_t * e)
{
    lv_screen_load_anim(screen_contacts(), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}
void on_navigation_clicked_cb(lv_event_t * e)
{
    lv_screen_load_anim(screen_navigation(), LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0, true);
}


void on_simulator_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *screen = lv_event_get_target(e);

    if (code == LV_EVENT_SCREEN_LOADED) {

        lv_screen_load(screen_home());

    }
}

void set_screen(int32_t w, int32_t h)
{
    lv_subject_set_int(&sb_screen_width, w);
    lv_subject_set_int(&sb_screen_height, h);

    lv_subject_set_int(&sb_screen_type, w == h ? 0 : 1);
    lv_subject_set_int(&sb_list_circular_mode, w == h ? 1 : 0);


    char buf[32];
    lv_snprintf(buf, sizeof(buf), "%dx%d", w, h);
    lv_subject_copy_string(&sb_screen_res, buf);
    
    if (w >= 400) {
        lv_subject_set_int(&sb_screen_size, 0); // 466
    } else if (w >= 300) {
        lv_subject_set_int(&sb_screen_size, 1); // 360
    } else {
        lv_subject_set_int(&sb_screen_size, 2); // 240
    }
}


/**********************
 *   STATIC FUNCTIONS
 **********************/

static void on_language_change(lv_event_t * e)
{
    const char * language = lv_event_get_param(e);
    LV_LOG_USER("Language changed to %s", language);

    lv_subject_set_int(&sb_language, lang_tag_get_index(language, 0));
}

static void language_observer_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    int32_t index = lv_subject_get_int(subject);
    LV_LOG_USER("Language index %d", index);

    lv_translation_set_language(lang_tag_get_by_index(index));

}




static void screen_res_cb(lv_event_t *e)
{
    lv_display_t * disp = lv_event_get_target(e);
    int32_t w = lv_display_get_original_horizontal_resolution(disp);
    int32_t h = lv_display_get_original_vertical_resolution(disp);

    set_screen(w, h);
}



void on_hs_info_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if (code == LV_EVENT_DELETE) {
        hs_info_layout_state_t * state = lv_obj_get_user_data(obj);
        if (state) {
            lv_free(state);
            lv_obj_set_user_data(obj, NULL);
        }
        return;
    }

    if (code != LV_EVENT_GET_SELF_SIZE) return;

    int32_t count = lv_obj_get_child_cnt(obj);
    int32_t p_width = lv_obj_get_width(obj);
    if (count != 2 || p_width == 0) return;

    lv_obj_t * child1 = lv_obj_get_child(obj, 0);
    lv_obj_t * child2 = lv_obj_get_child(obj, 1);

    int32_t width1 = lv_obj_get_width(child1);
    int32_t width2 = lv_obj_get_width(child2);

    lv_area_t cont_a;
    lv_obj_get_coords(child1, &cont_a);
    int32_t cont_h = lv_area_get_height(&cont_a);
    // LV_LOG_USER("Child1 height: %d", cont_h);

    if (width1 == 0 || width2 == 0) return;

    hs_info_layout_state_t * state = lv_obj_get_user_data(obj);
    if (state == NULL) {
        state = lv_malloc(sizeof(*state));
        if (state == NULL) return;

        state->parent_width = 0;
        state->child1_width = 0;
        state->child1_height = 0;
        state->child2_width = 0;
        state->overflow = false;
        lv_obj_set_user_data(obj, state);
    }

    bool forced_overflow_widths = state->overflow && width1 == p_width && width2 == p_width;
    if (forced_overflow_widths) {
        width1 = state->child1_width;
        width2 = state->child2_width;
    }

    bool changed = state->parent_width != p_width ||
                   state->child1_width != width1 ||
                   state->child2_width != width2 || state->child1_height != cont_h;
    if (!changed) return;

    bool overflow = width1 + width2 > p_width;

    state->parent_width = p_width;
    state->child1_width = width1;
    state->child2_width = width2;
    state->overflow = overflow;
    state->child1_height = cont_h;

    if (overflow) {
        lv_obj_set_width(child1, lv_pct(100));
        lv_obj_set_width(child2, lv_pct(100));
        lv_obj_update_layout(child1);

        lv_obj_set_y(child2, state->child1_height);

        // LV_LOG_USER("Overflow detected: width1=%d, height1=%d, width2=%d, parent_width=%d", width1, state->child1_height, width2, p_width);
    } else {
        lv_obj_set_width(child1, LV_SIZE_CONTENT);
        lv_obj_set_width(child2, LV_SIZE_CONTENT);
        lv_obj_set_align(child2, LV_ALIGN_TOP_RIGHT);
        lv_obj_set_y(child2, 0);
    }
}


static const char * lang_tag_get_by_index(int index)
{
    if(index < 0 || index >= LANG_TAG_COUNT) {
        return lang_tags[0];
    }

    return lang_tags[index];
}

static int lang_tag_get_index(const char * str, int def)
{
    if(str == NULL) {
        return 0;
    }

    for(int i = 0; i < LANG_TAG_COUNT; i++) {
        if(lv_streq(lang_tags[i], str)) {
            return i;
        }
    }

    return 0;
}