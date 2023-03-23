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

#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"
#include "nvs_flash.h"
#include "lvgl/lvgl.h"
#include "lvgl_helpers.h"

// wifi section

// #define EXAMPLE_ESP_WIFI_SSID "iqooneo5"
// #define EXAMPLE_ESP_WIFI_PASS "ctbCTB88.."
// #define EXAMPLE_ESP_MAXIMUM_RETRY 5

// #define CONFIG_ESP_WIFI_AUTH_WPA2_PSK 1

// #if CONFIG_ESP_WIFI_AUTH_OPEN
// #define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_OPEN
// #elif CONFIG_ESP_WIFI_AUTH_WEP
// #define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WEP
// #elif CONFIG_ESP_WIFI_AUTH_WPA_PSK
// #define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_PSK
// #elif CONFIG_ESP_WIFI_AUTH_WPA2_PSK
// #define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_PSK
// #elif CONFIG_ESP_WIFI_AUTH_WPA_WPA2_PSK
// #define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_WPA2_PSK
// #elif CONFIG_ESP_WIFI_AUTH_WPA3_PSK
// #define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA3_PSK
// #elif CONFIG_ESP_WIFI_AUTH_WPA2_WPA3_PSK
// #define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_WPA3_PSK
// #elif CONFIG_ESP_WIFI_AUTH_WAPI_PSK
// #define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WAPI_PSK
// #endif

// /* FreeRTOS event group to signal when we are connected*/
// static EventGroupHandle_t s_wifi_event_group;

// /* The event group allows multiple bits for each event, but we only care about two events:
//  * - we are connected to the AP with an IP
//  * - we failed to connect after the maximum amount of retries */
// #define WIFI_CONNECTED_BIT BIT0
// #define WIFI_FAIL_BIT BIT1

// static const char *TAG = "wifi station";

// static int s_retry_num = 0;

// static void wifi_event_handler(void *arg, esp_event_base_t event_base,
//                                int32_t event_id, void *event_data)
// {
//    page_container_t *wifi_scr_instance = (page_container_t *)arg;
//    wifi_page_t *wifi_page_instance = (wifi_page_t *)wifi_scr_instance->page;

//    switch (event_id)
//    {
//    case WIFI_EVENT_STA_START:
//       esp_wifi_connect();
//       break;
//    case WIFI_EVENT_STA_DISCONNECTED:
//       if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY)
//       {
//          esp_wifi_connect();
//          s_retry_num++;
//          ESP_LOGI(TAG, "retry to connect to the AP");
//       }
//       else
//       {
//          xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
//       }
//       ESP_LOGI(TAG, "connect to the AP fail");
//       wifi_page_update(wifi_page_instance, WIFI_STATUS, "DISCONNECTED");
//       break;
//    case WIFI_EVENT_STA_CONNECTED:
//       ESP_LOGI(TAG, "connect to the AP success");
//       wifi_page_update(wifi_page_instance, WIFI_STATUS, "CONNECTED");
//       wifi_page_update(wifi_page_instance, WIFI_SSID, EXAMPLE_ESP_WIFI_SSID);
//       break;
//    default:
//       break;
//    }
// }

// static void ip_event_handler(void *arg, esp_event_base_t event_base,
//                              int32_t event_id, void *event_data)
// {
//    page_container_t *wifi_scr_instance = (page_container_t *)arg;
//    wifi_page_t *wifi_page_instance = (wifi_page_t *)wifi_scr_instance->page;
//    switch (event_id)
//    {
//    case IP_EVENT_STA_GOT_IP:
//       ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
//       ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
//       s_retry_num = 0;
//       xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);

//       char ip_str[16];
//       sprintf(ip_str, IPSTR, IP2STR(&event->ip_info.ip));
//       wifi_page_update(wifi_page_instance, WIFI_IP, ip_str);
//    }
// }

// wifi section

page_container_t *soil_scr;
page_container_t *illuminance_scr;
page_container_t *wifi_scr;
page_container_t *weather_scr;

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

   // create all the pages of soil, illuminance, wifi and weather
   soil_scr = page_container_init(SOIL_PAGE);
   illuminance_scr = page_container_init(ILLUMINANCE_PAGE);
   weather_scr = page_container_init(WEATHER_PAGE);
   wifi_scr = page_container_init(WIFI_PAGE);

   // page_container_load(WIFI_PAGE, wifi_scr, wifi_scr);
   // page_container_load(SOIL_PAGE, soil_scr, soil_scr);

   // intialize the wifi
   // s_wifi_event_group = xEventGroupCreate();

   // ESP_ERROR_CHECK(esp_netif_init());

   // ESP_ERROR_CHECK(esp_event_loop_create_default());
   // esp_netif_create_default_wifi_sta();

   // wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
   // ESP_ERROR_CHECK(esp_wifi_init(&cfg));

   // esp_event_handler_instance_t instance_any_id;
   // esp_event_handler_instance_t instance_got_ip;
   // ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
   //                                                     ESP_EVENT_ANY_ID,
   //                                                     &wifi_event_handler,
   //                                                     wifi_scr,
   //                                                     &instance_any_id));
   // ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
   //                                                     IP_EVENT_STA_GOT_IP,
   //                                                     &ip_event_handler,
   //                                                     wifi_scr,
   //                                                     &instance_got_ip));

   // wifi_page_t *wifi_page_instance = (wifi_page_t *)wifi_scr->page;
   // wifi_page_update(wifi_page_instance, WIFI_STATUS, "Connecting to AP");

   // wifi_config_t wifi_config = {
   //     .sta = {
   //         .ssid = EXAMPLE_ESP_WIFI_SSID,
   //         .password = EXAMPLE_ESP_WIFI_PASS,
   //         /* Authmode threshold resets to WPA2 as default if password matches WPA2 standards (pasword len => 8).
   //          * If you want to connect the device to deprecated WEP/WPA networks, Please set the threshold value
   //          * to WIFI_AUTH_WEP/WIFI_AUTH_WPA_PSK and set the password with length and format matching to
   //          * WIFI_AUTH_WEP/WIFI_AUTH_WPA_PSK standards.
   //          */
   //         .threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD,
   //         .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
   //     },
   // };
   // ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
   // ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
   // ESP_ERROR_CHECK(esp_wifi_start());

   // ESP_LOGI(TAG, "wifi_init_sta finished.");

   // /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
   //  * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
   // EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
   //                                        WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
   //                                        pdFALSE,
   //                                        pdFALSE,
   //                                        portMAX_DELAY);

   // /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
   //  * happened. */
   // if (bits & WIFI_CONNECTED_BIT)
   // {
   //    ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
   //             EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
   // }
   // else if (bits & WIFI_FAIL_BIT)
   // {
   //    ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
   //             EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);

   //    // Delete event group
   //    vEventGroupDelete(s_wifi_event_group);
   //    // Delete event handler instances
   //    esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip);
   //    esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id);
   //    // Delete netif
   //    esp_netif_destroy(s_wifi_event_group);
   //    // Stop Wi-Fi
   //    esp_wifi_stop();
   //    // Deinitialize Wi-Fi
   //    esp_wifi_deinit();
   // }
   // else
   // {
   //    ESP_LOGE(TAG, "UNEXPECTED EVENT");
   //    // Delete event group
   //    vEventGroupDelete(s_wifi_event_group);
   //    // Delete event handler instances
   //    esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip);
   //    esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id);
   //    // Delete netif
   //    esp_netif_destroy(s_wifi_event_group);
   //    // Stop Wi-Fi
   //    esp_wifi_stop();
   //    // Deinitialize Wi-Fi
   //    esp_wifi_deinit();
   // }

   extern void wifi_init_state_task(void *parameters);
   xTaskCreate(wifi_init_state_task, "wifi_init_state_task", 2048 * 2, wifi_scr, 5, NULL);

   page_container_load(WIFI_PAGE, wifi_scr, wifi_scr);

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
