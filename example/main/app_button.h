#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"
#include "esp_log.h"
#include "unity.h"
#include "iot_button.h"

void button_init();


#ifdef __cplusplus
}
#endif
