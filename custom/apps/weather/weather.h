/**
 * @file weather.h
 * @brief Weather data API
 */

#ifndef HELIOS_WEATHER_H
#define HELIOS_WEATHER_H

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

/*********************
 *      DEFINES
 *********************/

#define HELIOS_HOURLY_FORECAST_MAX       12
#define HELIOS_DAILY_FORECAST_MAX        7
#define HELIOS_WEATHER_TEXT_MAX          16

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    const void * icon;
    char time[HELIOS_WEATHER_TEXT_MAX];
    char temp[HELIOS_WEATHER_TEXT_MAX];
    char humidity[HELIOS_WEATHER_TEXT_MAX];
} helios_hourly_forecast_t;

typedef struct {
    const void * icon;
    char day[HELIOS_WEATHER_TEXT_MAX];
    char temp[HELIOS_WEATHER_TEXT_MAX];
} helios_daily_forecast_t;

typedef enum {
    HELIOS_WEATHER_EVENT_CHANGED,
} helios_weather_event_t;

typedef void (*helios_weather_observer_cb_t)(helios_weather_event_t event, void * user_data);

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void helios_weather_init(void);

uint32_t helios_weather_hourly_count(void);
const helios_hourly_forecast_t * helios_weather_hourly_get(uint32_t index);

uint32_t helios_weather_daily_count(void);
const helios_daily_forecast_t * helios_weather_daily_get(uint32_t index);

bool helios_weather_hourly_add(const void * icon, const char * time, const char * temp, const char * humidity);
bool helios_weather_daily_add(const void * icon, const char * day, const char * temp);
void helios_weather_hourly_clear(void);
void helios_weather_daily_clear(void);

bool helios_weather_observer_add(helios_weather_observer_cb_t cb, void * user_data);
void helios_weather_observer_remove(helios_weather_observer_cb_t cb, void * user_data);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*HELIOS_WEATHER_H*/
