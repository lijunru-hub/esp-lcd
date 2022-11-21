#ifndef APP_BUTTON_H
#define APP_BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "app_button.h"

static const char *TAG = "BUTTON TEST";

#define BUTTON_IO_NUM  0
#define BUTTON_ACTIVE_LEVEL   0
#define BUTTON_NUM 16

char *a = "cbc";

static button_handle_t g_btns[BUTTON_NUM] = {0};

static int get_btn_index(button_handle_t btn)
{
    for (size_t i = 0; i < BUTTON_NUM; i++) {
        if (btn == g_btns[i]) {
            return i;
        }
    }
    return -1;
}

static void button_press_down_cb(void *arg,void *data)
{
    TEST_ASSERT_EQUAL_HEX(BUTTON_PRESS_DOWN, iot_button_get_event(arg));
    ESP_LOGI(TAG, "BTN%d: BUTTON_PRESS_DOWN %s", get_btn_index((button_handle_t)arg),(char *)a);
}

static void button_press_up_cb(void *arg,void *data)
{
    TEST_ASSERT_EQUAL_HEX(BUTTON_PRESS_UP, iot_button_get_event(arg));
    ESP_LOGI(TAG, "BTN%d: BUTTON_PRESS_UP", get_btn_index((button_handle_t)arg));
}

static void button_press_repeat_cb(void *arg,void *data)
{
    ESP_LOGI(TAG, "BTN%d: BUTTON_PRESS_REPEAT[%d]", get_btn_index((button_handle_t)arg), iot_button_get_repeat((button_handle_t)arg));
}

static void button_single_click_cb(void *arg,void *data)
{
    TEST_ASSERT_EQUAL_HEX(BUTTON_SINGLE_CLICK, iot_button_get_event(arg));
    ESP_LOGI(TAG, "BTN%d: BUTTON_SINGLE_CLICK", get_btn_index((button_handle_t)arg));
}

static void button_double_click_cb(void *arg,void *data)
{
    TEST_ASSERT_EQUAL_HEX(BUTTON_DOUBLE_CLICK, iot_button_get_event(arg));
    ESP_LOGI(TAG, "BTN%d: BUTTON_DOUBLE_CLICK", get_btn_index((button_handle_t)arg));
}

static void button_long_press_start_cb(void *arg,void *data)
{
    TEST_ASSERT_EQUAL_HEX(BUTTON_LONG_PRESS_START, iot_button_get_event(arg));
    ESP_LOGI(TAG, "BTN%d: BUTTON_LONG_PRESS_START", get_btn_index((button_handle_t)arg));
}

static void button_long_press_hold_cb(void *arg,void *data)
{
    TEST_ASSERT_EQUAL_HEX(BUTTON_LONG_PRESS_HOLD, iot_button_get_event(arg));
    ESP_LOGI(TAG, "BTN%d: BUTTON_LONG_PRESS_HOLD", get_btn_index((button_handle_t)arg));
}

static void print_button_event(button_handle_t btn)
{
    button_event_t evt = iot_button_get_event(btn);
    switch (evt) {
    case BUTTON_PRESS_DOWN:
        ESP_LOGI(TAG, "BUTTON_PRESS_DOWN");
        break;
    case BUTTON_PRESS_UP:
        ESP_LOGI(TAG, "BUTTON_PRESS_UP");
        break;
    case BUTTON_PRESS_REPEAT:
        ESP_LOGI(TAG, "BUTTON_PRESS_REPEAT");
        break;
    case BUTTON_SINGLE_CLICK:
        ESP_LOGI(TAG, "BUTTON_SINGLE_CLICK");
        break;
    case BUTTON_DOUBLE_CLICK:
        ESP_LOGI(TAG, "BUTTON_DOUBLE_CLICK");
        break;
    case BUTTON_LONG_PRESS_START:
        ESP_LOGI(TAG, "BUTTON_LONG_PRESS_START");
        break;
    case BUTTON_LONG_PRESS_HOLD:
        ESP_LOGI(TAG, "BUTTON_LONG_PRESS_HOLD");
        break;

    default:
        break;
    }
}

void button_init()
{
    button_config_t cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = 42,
            .active_level = 0,
        },
    };
    g_btns[0] = iot_button_create(&cfg);
    TEST_ASSERT_NOT_NULL(g_btns[0]);
    iot_button_register_cb(g_btns[0], BUTTON_PRESS_DOWN, button_press_down_cb,a);
    iot_button_register_cb(g_btns[0], BUTTON_PRESS_UP, button_press_up_cb,NULL);
    iot_button_register_cb(g_btns[0], BUTTON_PRESS_REPEAT, button_press_repeat_cb,NULL);
    iot_button_register_cb(g_btns[0], BUTTON_SINGLE_CLICK, button_single_click_cb,NULL);
    iot_button_register_cb(g_btns[0], BUTTON_DOUBLE_CLICK, button_double_click_cb,NULL);
    iot_button_register_cb(g_btns[0], BUTTON_LONG_PRESS_START, button_long_press_start_cb,NULL);
    iot_button_register_cb(g_btns[0], BUTTON_LONG_PRESS_HOLD, button_long_press_hold_cb,NULL);
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    iot_button_delete(g_btns[0]);
}

#ifdef __cplusplus
}
#endif

#endif