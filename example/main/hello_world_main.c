/*
 * @Author: LiJunu lijunru@espressif.com
 * @Date: 2022-08-29 14:38:15
 * @LastEditors: LiJunu lijunru@espressif.com
 * @LastEditTime: 2022-11-21 10:35:30
 * @FilePath: /esp-lcd/example/main/hello_world_main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "gc9a01.h"
#include "driver/gpio.h"
#include "app_cnt.h"

#include "esp_log.h"

#include "app_button.h"

#define STACK_SIZE     2048

static const char *TAG = "ESP_KNOB"; 

void LCD(void *arg)
{
    uint16_t Color;
    GC9A01_Init();
    for(;;)
    {
        Color=rand();
        GC9A01_FillRect(0,0,239,239,Color);
        GC9A01_Update();
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

// void EC11(void *arg){
//     for(;;)
//     {
//         EC11_Display();
//         ESP_LOGI(TAG,"%d",get_count());
//         vTaskDelay(1/portTICK_PERIOD_MS);
//     }
// }

void app_main(void)
{
    button_init();
    //EC11_init();
    //xTaskCreate(EC11,"Test EC!!",STACK_SIZE,NULL,tskIDLE_PRIORITY,NULL);
    /* Print chip information */
    // gpio_isr_init();
    // TaskHandle_t LCDHandle;
    // xTaskCreate(LCD,"Test LCD",STACK_SIZE,NULL,tskIDLE_PRIORITY,&LCDHandle);
    // configASSERT(LCDHandle);
}
