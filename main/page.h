#ifndef __PAGE_H__
#define __PAGE_H__

#include "lvgl.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

typedef struct
{
    SemaphoreHandle_t mux;

    // define the page model
    lv_obj_t *label_status;
    lv_obj_t *label_ip;
    lv_obj_t *label_ssid;
} wifi_page_t;

typedef struct
{
    SemaphoreHandle_t mux;

    // define the page model
    lv_obj_t *moisture;
} soil_page_t;

typedef struct
{
    SemaphoreHandle_t mux;

    // define the page model
    lv_obj_t *illuminance;
} illuminance_page_t;

typedef struct
{
    SemaphoreHandle_t mux;

    // define the page model
    lv_obj_t *temperature;
    lv_obj_t *humidity;
    lv_obj_t *pressure;
} weather_page_t;

enum page_type
{
    WIFI_STATUS,
    WIFI_IP,
    WIFI_SSID,
    SOIL_MOISTURE,
    ILLUMINANCE_ILLUMINANCE,
    WEATHER_HUMIDITY,
    WEATHER_TEMPERATURE,
    WEATHER_PRESSURE

};
wifi_page_t *wifi_page_init(lv_obj_t *src);
void wifi_page_deinit(wifi_page_t *page);
int wifi_page_update(enum page_type ptype, void *value);

soil_page_t *soil_page_init(lv_obj_t *src);
void soil_page_deinit(soil_page_t *page);
int soil_page_update(enum page_type ptype, void *value);

illuminance_page_t *illuminance_page_init(lv_obj_t *src);
void illuminance_page_deinit(illuminance_page_t *page);
int illuminance_page_update(enum page_type ptype, void *value);

weather_page_t *weather_page_init(lv_obj_t *src);
void weather_page_deinit(weather_page_t *page);
int weather_page_update(enum page_type ptype, void *value);

#endif // __PAGE_H__