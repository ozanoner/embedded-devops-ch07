
#include "esp_log.h"
#include "iot_button.h"
#include "button_gpio.h"
#include "devops_easy_connect.h"
#include "log_history.h"

static const char *LOG_TAG = "app";
static const char *WIFI_SSID = "Wokwi-GUEST";
static const char *WIFI_PASS = "";
static const int APP_BUTTON_GPIO = 9;

static button_handle_t app_button = NULL;

static void app_single_click_cb(void *button_handle, void *usr_data);
static void app_long_press_cb(void *button_handle, void *usr_data);
static void on_connected(void *arg);

void app_main(void)
{
    LogHistory_init();

    ESP_LOGI(LOG_TAG, "The app is starting...");
    app_wifi_init(WIFI_SSID, WIFI_PASS, on_connected, NULL);
    app_wifi_connect();

    const button_config_t button_cfg = {0};
    const button_gpio_config_t gpio_cfg = {
        .gpio_num = APP_BUTTON_GPIO};

    iot_button_new_gpio_device(&button_cfg, &gpio_cfg, &app_button);
    iot_button_register_cb(app_button, BUTTON_SINGLE_CLICK, NULL, app_single_click_cb, NULL);
    iot_button_register_cb(app_button, BUTTON_LONG_PRESS_START, NULL, app_long_press_cb, NULL);
}

static void app_single_click_cb(void *button_handle, void *usr_data)
{
    ESP_LOGD(LOG_TAG, "Button single-click detected");
}

static void app_long_press_cb(void *button_handle, void *usr_data)
{
    ESP_LOGD(LOG_TAG, "Button long-press detected");
    LogHistory_dump();
}

static void on_connected(void *arg)
{
    ESP_LOGD(LOG_TAG, "Wi-Fi connected");
}
