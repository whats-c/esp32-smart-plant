// the page.c define the page model of soil, illuminance, wifi, weather, etc.

#include "lvgl.h"
#include "page.h"

page_container_t *page_container_init(enum container_type ctype)
{
    page_container_t *page_container_instance = malloc(sizeof(page_container_t));
    page_container_instance->mux = xSemaphoreCreateMutex();
    lv_obj_t *scr = lv_obj_create(NULL);
    lv_obj_add_flag(scr, LV_OBJ_FLAG_HIDDEN);

    switch (ctype)
    {
    case SOIL_PAGE:
        // configure the soil page screen object
        lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);
        page_container_instance->page = soil_page_init(scr);
        break;
    case ILLUMINANCE_PAGE:
        // configure the soil page screen object
        lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);
        page_container_instance->page = illuminance_page_init(scr);
        break;
    case WIFI_PAGE:
        // configure the soil page screen object
        lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);
        page_container_instance->page = wifi_page_init(scr);
        break;
    case WEATHER_PAGE:
        // configure the soil page screen object
        lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);
        page_container_instance->page = weather_page_init(scr);
        break;
    default:
        return NULL;
    }

    return page_container_instance;
}

void page_container_deinit(page_container_t *page_container_instance)
{
    if (page_container_instance != NULL)
    {
        free(page_container_instance);
    }
}

void page_container_load(enum container_type ctype, page_container_t *container_current, page_container_t *container)
{
    switch (ctype)
    {
    case SOIL_PAGE:
        // switch shows page to soil page
        lv_obj_add_flag(container_current->scr, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(container->scr, LV_OBJ_FLAG_HIDDEN);
        // load the soil page components
        break;
    case ILLUMINANCE_PAGE:
        // switch shows page to illuminance page
        lv_obj_add_flag(container_current->scr, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(container->scr, LV_OBJ_FLAG_HIDDEN);
        // load the illuminance page components
        break;
    case WIFI_PAGE:
        // switch shows page to wifi page
        lv_obj_add_flag(container_current->scr, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(container->scr, LV_OBJ_FLAG_HIDDEN);
        // load the wifi page components
        break;
    case WEATHER_PAGE:
        // switch shows page to weather page
        lv_obj_add_flag(container_current->scr, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(container->scr, LV_OBJ_FLAG_HIDDEN);
        // load the weather page components
        break;
    default:
        break;
    }
}

// define the wifi page interface
wifi_page_t *wifi_page_init(lv_obj_t *src)
{
    // get the default parent object, if the src is empty
    if (src == NULL)
    {
        src = lv_disp_get_scr_act(NULL);
    }

    wifi_page_t *wifi_page_instance = malloc(sizeof(wifi_page_t));
    wifi_page_instance->mux = xSemaphoreCreateMutex();

    // create the wifi page all of elements
    wifi_page_instance->label_status = lv_label_create(src);
    wifi_page_instance->label_ip = lv_label_create(src);
    wifi_page_instance->label_ssid = lv_label_create(src);

    // create a font style object
    lv_style_t *font_style = malloc(sizeof(lv_style_t));
    lv_style_init(font_style);
    lv_style_set_text_font(font_style, LV_STATE_DEFAULT, &lv_font_montserrat_8);
    lv_style_set_text_color(font_style, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
    lv_style_set_text_align(font_style, LV_STATE_DEFAULT, LV_TEXT_ALIGN_LEFT);

    // add the font style to the labels
    lv_obj_add_style(wifi_page_instance->label_status, LV_LABEL_PART_MAIN, font_style);
    lv_obj_add_style(wifi_page_instance->label_ip, LV_LABEL_PART_MAIN, font_style);
    lv_obj_add_style(wifi_page_instance->label_ssid, LV_LABEL_PART_MAIN, font_style);

    // set the label text
    lv_label_set_text(wifi_page_instance->label_status, "Status: ");
    lv_label_set_text(wifi_page_instance->label_ip, "IP: ");
    lv_label_set_text(wifi_page_instance->label_ssid, "SSID: ");

    // set the label position
    lv_obj_align(wifi_page_instance->label_status, LV_ALIGN_IN_TOP_LEFT, 10, 10);
    lv_obj_align(wifi_page_instance->label_ip, LV_ALIGN_IN_TOP_LEFT, 10, 30);
    lv_obj_align(wifi_page_instance->label_ssid, LV_ALIGN_IN_TOP_LEFT, 10, 50);

    return wifi_page_instance;
}

int wifi_page_update(wifi_page_t *wifi_page_instance, enum page_type ptype, void *value)
{
    switch (ptype)
    {
    case WIFI_STATUS:
        lv_label_set_text_fmt(wifi_page_instance->label_status, "%s", (char *)value);
    case WIFI_IP:
        lv_label_set_text_fmt(wifi_page_instance->label_ip, "%s", (char *)value);
    case WIFI_SSID:
        lv_label_set_text_fmt(wifi_page_instance->label_ssid, "%s", (char *)value);
    default:
        return -1;
    }

    return 0;
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

    soil_page_t *soil_page_instance = malloc(sizeof(soil_page_t));
    soil_page_instance->mux = xSemaphoreCreateMutex();

    // create the soil page all of elements
    soil_page_instance->moisture = lv_label_create(src);

    // create a font style object
    lv_style_t *font_style = malloc(sizeof(lv_style_t));
    lv_style_init(font_style);
    lv_style_set_text_font(font_style, LV_STATE_DEFAULT, &lv_font_montserrat_8);
    lv_style_set_text_color(font_style, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
    lv_style_set_text_align(font_style, LV_STATE_DEFAULT, LV_TEXT_ALIGN_LEFT);

    // add the font style to the labels
    lv_obj_add_style(soil_page_instance->moisture, LV_LABEL_PART_MAIN, font_style);

    // set the label text
    lv_label_set_text(soil_page_instance->moisture, "Moisture: ");

    // set the label position
    lv_obj_align(soil_page_instance->moisture, LV_ALIGN_IN_TOP_LEFT, 10, 10);

    return soil_page_instance;
}

int soil_page_update(soil_page_t *soil_page_instance, enum page_type ptype, void *value)
{
    switch (ptype)
    {
    case SOIL_MOISTURE:

    default:
        break;
    }
    return 0;
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

    illuminance_page_t *illuminance_page_instance = malloc(sizeof(illuminance_page_t));
    illuminance_page_instance->mux = xSemaphoreCreateMutex();

    // create the illuminance page all of elements
    illuminance_page_instance->illuminance = lv_label_create(src);

    // create a font style object
    lv_style_t *font_style = malloc(sizeof(lv_style_t));
    lv_style_init(font_style);
    lv_style_set_text_font(font_style, LV_STATE_DEFAULT, &lv_font_montserrat_8);
    lv_style_set_text_color(font_style, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
    lv_style_set_text_align(font_style, LV_STATE_DEFAULT, LV_TEXT_ALIGN_LEFT);

    // add the font style to the labels
    lv_obj_add_style(illuminance_page_instance->illuminance, LV_LABEL_PART_MAIN, font_style);

    // set the label text
    lv_label_set_text(illuminance_page_instance->illuminance, "Illuminance: ");

    // set the label position
    lv_obj_align(illuminance_page_instance->illuminance, LV_ALIGN_IN_TOP_LEFT, 10, 10);

    return illuminance_page_instance;
}

int illuminance_page_update(illuminance_page_t illuminance_page_instance, enum page_type ptype, void *value)
{
    switch (ptype)
    {
    case ILLUMINANCE_ILLUMINANCE:

    default:
        break;
    }
    return 0;
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

    weather_page_t *weather_page_instance = malloc(sizeof(weather_page_t));
    weather_page_instance->mux = xSemaphoreCreateMutex();

    // create the weather page all of elements
    weather_page_instance->temperature = lv_label_create(src);
    weather_page_instance->humidity = lv_label_create(src);
    weather_page_instance->pressure = lv_label_create(src);

    // create a font style object
    lv_style_t *font_style = malloc(sizeof(lv_style_t));
    lv_style_init(font_style);
    lv_style_set_text_font(font_style, LV_STATE_DEFAULT, &lv_font_montserrat_8);
    lv_style_set_text_color(font_style, LV_STATE_DEFAULT, lv_color_hex(0xffffff));
    lv_style_set_text_align(font_style, LV_STATE_DEFAULT, LV_TEXT_ALIGN_LEFT);

    // add the font style to the labels
    lv_obj_add_style(weather_page_instance->temperature, LV_LABEL_PART_MAIN, font_style);
    lv_obj_add_style(weather_page_instance->humidity, LV_LABEL_PART_MAIN, font_style);
    lv_obj_add_style(weather_page_instance->pressure, LV_LABEL_PART_MAIN, font_style);

    // set the label text
    lv_label_set_text(weather_page_instance->temperature, "Temperature: ");
    lv_label_set_text(weather_page_instance->humidity, "Humidity: ");
    lv_label_set_text(weather_page_instance->pressure, "Pressure: ");

    // set the label position
    lv_obj_align(weather_page_instance->temperature, LV_ALIGN_IN_TOP_LEFT, 10, 10);
    lv_obj_align(weather_page_instance->humidity, LV_ALIGN_IN_TOP_LEFT, 10, 20);
    lv_obj_align(weather_page_instance->pressure, LV_ALIGN_IN_TOP_LEFT, 10, 30);

    return weather_page_instance;
}

int weather_page_update(weather_page_t *weather_page_instance, enum page_type ptype, void *value)
{
    switch (ptype)
    {
    case WEATHER_TEMPERATURE:

    case WEATHER_HUMIDITY:

    case WEATHER_PRESSURE:

    default:
        break;
    }

    return 0;
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