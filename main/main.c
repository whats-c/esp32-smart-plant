/*
 * @Descripttion :
 * @version      :
 * @Author       : Kevincoooool
 * @Date         : 2021-09-04 16:11:59
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-09-04 18:05:01
 * @FilePath     : \lvgl_v8\main\main.c
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "lv_examples/src/lv_demo_widgets/lv_demo_widgets.h"
#include "lv_examples/src/lv_demo_music/lv_demo_music.h"
#include "lv_examples/src/lv_demo_benchmark/lv_demo_benchmark.h"
#include "lvgl_helpers.h"
#include "esp_freertos_hooks.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"

#include "lvgl/examples/lv_examples.h"

#include "page.h"

lv_obj_t *soil_scr;
lv_obj_t *illuminance_scr;
lv_obj_t *wifi_scr;
lv_obj_t *weather_scr;

LV_IMG_DECLARE(astronauts0) // 包含图片资源文件
LV_IMG_DECLARE(astronauts1) // 包含图片资源文件
LV_IMG_DECLARE(astronauts2) // 包含图片资源文件

static const lv_img_dsc_t *astronauts_anim_imgs[3] = {
    &astronauts0,
    &astronauts1,
    &astronauts2,
};

void astronauts_animing(void)
{
   lv_obj_t *animimg1 = lv_animimg_create(lv_scr_act());                       // 创建动画对象
   lv_obj_center(animimg1);                                                    // 将对象置于屏幕中央
   lv_animimg_set_src(animimg1, (lv_img_decoder_t **)astronauts_anim_imgs, 3); // 加载动画资源
   lv_animimg_set_duration(animimg1, 500);                                     // 创建动画时间
   lv_animimg_set_repeat_count(animimg1, LV_ANIM_REPEAT_INFINITE);             // 设置一直重复时间
   lv_animimg_start(animimg1);
}

static void lv_tick_task(void *arg)
{
   (void)arg;
   lv_tick_inc(portTICK_PERIOD_MS);
}
SemaphoreHandle_t xGuiSemaphore;

/**
 * Basic example to create a "Hello world" label
 */
void lv_example_get_started_1(void)
{
   /*Change the active screen's background color*/
   lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);

   /*Create a white label, set its text and align it to the center*/
   lv_obj_t *label = lv_label_create(lv_scr_act());
   lv_label_set_text(label, "Hello");
   lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
   lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

// static void gui_task(void *arg)
// {
//    xGuiSemaphore = xSemaphoreCreateMutex();
//    lv_init();          // lvgl内核初始化
//    lvgl_driver_init(); // lvgl显示接口初始化

//    /* Example for 1) */
//    static lv_disp_draw_buf_t draw_buf;
//    lv_color_t *buf1 = heap_caps_malloc(DLV_HOR_RES_MAX * DLV_VER_RES_MAX * sizeof(lv_color_t), MALLOC_CAP_DMA);
//    lv_color_t *buf2 = heap_caps_malloc(DLV_HOR_RES_MAX * DLV_VER_RES_MAX * sizeof(lv_color_t), MALLOC_CAP_DMA);

//    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, DLV_HOR_RES_MAX * DLV_VER_RES_MAX); /*Initialize the display buffer*/

//    static lv_disp_drv_t disp_drv;         /*A variable to hold the drivers. Must be static or global.*/
//    lv_disp_drv_init(&disp_drv);           /*Basic initialization*/
//    disp_drv.draw_buf = &draw_buf;         /*Set an initialized buffer*/
//    disp_drv.flush_cb = disp_driver_flush; /*Set a flush callback to draw to the display*/
//    disp_drv.hor_res = 80;                 /*Set the horizontal resolution in pixels*/
//    disp_drv.ver_res = 160;                /*Set the vertical resolution in pixels*/
//    lv_disp_drv_register(&disp_drv);       /*Register the driver and save the created display objects*/

//    esp_register_freertos_tick_hook(lv_tick_task);
//    lv_demo_widgets();
//    // lv_demo_music();
//    // astronauts_animing();
//    // lv_example_animimg_1();
//    // lv_demo_benchmark();

//    // lv_example_get_started_1();
//    // lv_wifi_page();

//    while (1)
//    {
//       /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
//       vTaskDelay(pdMS_TO_TICKS(10));

//       /* Try to take the semaphore, call lvgl related function on success */
//       if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
//       {
//          lv_timer_handler();
//          xSemaphoreGive(xGuiSemaphore);
//       }
//    }
// }

// the app main function include the lvgl task function
void app_main(void)
{
   // Initialize NVS flash
   esp_err_t ret = nvs_flash_init();
   if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
   {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
   }
   ESP_ERROR_CHECK(ret);

   xGuiSemaphore = xSemaphoreCreateMutex();
   lv_init();          // lvgl内核初始化
   lvgl_driver_init(); // lvgl显示接口初始化

   /* Example for 1) */
   static lv_disp_draw_buf_t draw_buf;
   lv_color_t *buf1 = heap_caps_malloc(DLV_HOR_RES_MAX * DLV_VER_RES_MAX * sizeof(lv_color_t), MALLOC_CAP_DMA);
   lv_color_t *buf2 = heap_caps_malloc(DLV_HOR_RES_MAX * DLV_VER_RES_MAX * sizeof(lv_color_t), MALLOC_CAP_DMA);

   lv_disp_draw_buf_init(&draw_buf, buf1, buf2, DLV_HOR_RES_MAX * DLV_VER_RES_MAX); /*Initialize the display buffer*/

   static lv_disp_drv_t disp_drv;         /*A variable to hold the drivers. Must be static or global.*/
   lv_disp_drv_init(&disp_drv);           /*Basic initialization*/
   disp_drv.draw_buf = &draw_buf;         /*Set an initialized buffer*/
   disp_drv.flush_cb = disp_driver_flush; /*Set a flush callback to draw to the display*/
   disp_drv.hor_res = 160;                /*Set the horizontal resolution in pixels*/
   disp_drv.ver_res = 80;                 /*Set the vertical resolution in pixels*/
   lv_disp_drv_register(&disp_drv);       /*Register the driver and save the created display objects*/

   esp_register_freertos_tick_hook(lv_tick_task);

   // change the display to landscape mode
   // Get a pointer to the default display object
   // lv_disp_t *disp = lv_disp_get_default();
   // // Set its rotation to 90 degrees
   // lv_disp_set_rotation(disp, LV_DISP_ROT_90);

   // lv_demo_widgets();
   // lv_demo_music();
   // astronauts_animing();
   // lv_example_animimg_1();
   // lv_demo_benchmark();

   // lv_example_get_started_1();
   // lv_wifi_page();

   // create the default page and shows it

   // create all the pages of soil, illuminance, wifi and weather
   soil_scr = page_container_init(SOIL_PAGE);
   illuminance_scr = page_container_init(ILLUMINANCE_PAGE);
   weather_scr = page_container_init(WEATHER_PAGE);
   wifi_scr = page_container_init(WIFI_PAGE);

   extern void wifi_init_state_task(void *pvParameter);
   wifi_page_t *wifi_page_instance = wifi_page_init(lv_scr_act());
   xTaskCreate(wifi_init_state_task, "wifi_init_state_task", 1024 * 5, wifi_page_instance, 5, NULL);

   while (1)
   {
      /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
      vTaskDelay(pdMS_TO_TICKS(10));

      /* Try to take the semaphore, call lvgl related function on success */
      if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
      {
         lv_timer_handler();
         xSemaphoreGive(xGuiSemaphore);
      }
   }
}
