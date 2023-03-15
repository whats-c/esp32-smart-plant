// the soil-page shows the soil moisture information and the illumination information

// main.c
#include "yl69.h"

char soil_page[1024];

// the task init the soil moisture sensor and get the soil moisture
void soil_task_handler(void *parameters)
{
    uint32_t value = 0;

    // init the soil moisture sensor
    yl69_setup(ADC_CHANNEL_6);

    while (is_running)
    {
        uint32_t adc_reading = yl69_read();
        uint32_t adc_percentage = yl69_normalization(adc_reading);
        snprintf(soil_page, sizeof(yl69_buffer), "{\"soil_mosture\": %d}", adc_percentage);
        printf("%s\n", soil_page);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}
