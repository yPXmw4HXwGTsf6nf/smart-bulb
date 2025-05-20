#include "led_driver.h"
#include "driver/ledc.h"
#include "esp_log.h"

static const char *TAG = "led_driver";
static const ledc_channel_t LED_CH = LEDC_CHANNEL_0;

void led_driver_init(void)
{
    /* 8‑bit pwm on gpio 2 */
    ledc_timer_config_t tcfg = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_8_BIT,
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = 1000,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&tcfg));

    ledc_channel_config_t ccfg = {
        .gpio_num   = 2,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel    = LED_CH,
        .timer_sel  = LEDC_TIMER_0,
        .duty       = 0,
        .hpoint     = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ccfg));

    ESP_LOGI(TAG,"pwm setup complete");
}

void led_set_white(uint8_t level)
{
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LED_CH, level));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LED_CH));
}
