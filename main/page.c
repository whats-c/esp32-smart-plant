// the page.c define the page model of soil, illuminance, wifi, weather, etc.

#include "lvgl.h"
#include "page.h"

// define the wifi page interface
wifi_page_t *wifi_page_init(lv_obj_t *src)
{
    // get the default parent object, if the src is empty
    if (src == NULL)
    {
        src = lv_disp_get_scr_act(NULL);
    }

    wifi_page_instance = malloc(sizeof(wifi_page_t));
    wifi_page_instance->mux = xSemaphoreCreateMutex();

    // create the wifi page all of elements
    label_status = lv_label_create(src);
    label_ip = lv_label_create(src);
    label_ssid = lv_label_create(src);

    return wifi_page_instance;
}

int wifi_page_update(label string, void *value)
{
    switch (label)
    {
    case "status":

    case "ip":

    case "ssid":

    default:
        break;
    }
}

// deinitialize the wifi page
void wifi_page_deinit(wifi_page_t *wifi_page_instance)
{
    if (wifi_page_instance != NULL)
    {
        free(wifi_page_instance);
    }
}

// define the soil page interface
soil_page_t *soil_page_init(lv_obj_t *src)
{
    // get the default parent object, if the src is empty
    if (src == NULL)
    {
        src = lv_disp_get_scr_act(NULL);
    }

    soil_page_instance = malloc(sizeof(soil_page_t));
    soil_page_instance->mux = xSemaphoreCreateMutex();

    // create the soil page all of elements
    moisture = lv_label_create(src);

    return soil_page_instance;
}

int soil_page_update(label string, void *value)
{
    switch (label)
    {
    case "moisture":

    default:
        break;
    }
}

// deinitialize the soil page
void soil_page_deinit(soil_page_t *soil_page_instance)
{
    if (soil_page_instance != NULL)
    {
        free(soil_page_instance);
    }
}

// define the illuminance page interface
illuminance_page_t *illuminance_page_init(lv_obj_t *src)
{
    // get the default parent object, if the src is empty
    if (src == NULL)
    {
        src = lv_disp_get_scr_act(NULL);
    }

    illuminance_page_instance = malloc(sizeof(illuminance_page_t));
    illuminance_page_instance->mux = xSemaphoreCreateMutex();

    // create the illuminance page all of elements
    illuminance = lv_label_create(src);

    return illuminance_page_instance;
}

int illuminance_page_update(label string, void *value)
{
    switch (label)
    {
    case "illuminance":

    default:
        break;
    }
}

// deinitialize the illuminance page
void illuminance_page_deinit(illuminance_page_t *illuminance_page_instance)
{
    if (illuminance_page_instance != NULL)
    {
        free(illuminance_page_instance);
    }
}

// define the weather page interface
weather_page_t *weather_page_init(lv_obj_t *src)
{
    // get the default parent object, if the src is empty
    if (src == NULL)
    {
        src = lv_disp_get_scr_act(NULL);
    }

    weather_page_instance = malloc(sizeof(weather_page_t));
    weather_page_instance->mux = xSemaphoreCreateMutex();

    // create the weather page all of elements
    temperature = lv_label_create(src);
    humidity = lv_label_create(src);
    pressure = lv_label_create(src);

    return weather_page_instance;
}

int weather_page_update(label string, void *value)
{
    switch (label)
    {
    case "temperature":

    case "humidity":

    case "pressure":

    default:
        break;
    }
}

// deinitialize the weather page
void weather_page_deinit(weather_page_t *weather_page_instance)
{
    if (weather_page_instance != NULL)
    {
        free(weather_page_instance);
    }
}

// Path: main\main.c