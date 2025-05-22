/**
 * @file led_driver.c
* @brief 8‑bit pwm driver for a single‑channel (white) led on esp‑idf.
 *
* this module wraps esp‑idf’s ledc driver to provide:
*   a reusable initialization routine (`led_driver_init`) that sets up a
*     low‑speed pwm timer and channel.
*   a runtime guard that prevents accidental double‑initialization.
*   a convenience setter (`led_set_white`) that clamps the duty cycle
*     and updates hardware registers.
*
* only one gpio / pwm channel is configured here for simplicity. additional
* channels (rgbw, cct, etc.) can be added by duplicating the macro set and
* extending the channel configuration table.
 */
#include "led_driver.h"
#include "driver/ledc.h"

#include "esp_log.h"
/* tag used for esp‑idf logging macros */
static const char *TAG = "led_driver";

/* -------- configuration macros -------- */
/** gpio the white led is attached to. adjust to match your board layout. */
#define LED_DRV_GPIO_WHITE      2
/** pwm frequency in hertz. 1 khz avoids audible noise while giving fine resolution. */
#define PWM_FREQ_HZ             1000
/** duty‑cycle resolution. 8‑bit is plenty for visible brightness steps. */
#define PWM_RESOLUTION          LEDC_TIMER_8_BIT
/** which ledc timer is used. keep unique if you add more channels. */
#define LEDC_TIMER              LEDC_TIMER_0
/** low‑speed mode lets us use most gpios without clock restrictions. */
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
/** hardware channel mapped to the white led. */
#define LEDC_CHANNEL_WHITE      LEDC_CHANNEL_0


/* keeps track of whether the driver has been set up to prevent re‑init. */
static bool s_initialized = false;

/**
* @brief initialize the led pwm driver.
*
* configures the ledc timer and channel associated with the white led.
* the function is idempotent: subsequent calls after successful setup
* return early and emit a warning.
 */

void led_driver_init(void)
{
    /* guard clause: exit early if someone calls init twice. */
    if (s_initialized) {
        ESP_LOGW(TAG, "led driver already initialized");
        return;
    }

    /* ---- configure the pwm timer ---- */
    /* the timer sets the global frequency and resolution common
       to any channels attached to it. */
    ledc_timer_config_t tcfg = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = PWM_RESOLUTION,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = PWM_FREQ_HZ,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&tcfg));

    /* ---- configure the pwm channel ---- */
    /* each led gets its own channel that maps the timer to a gpio. */
    ledc_channel_config_t ccfg = {
        .gpio_num   = LED_DRV_GPIO_WHITE,
        .speed_mode = LEDC_MODE,
        .channel    = LEDC_CHANNEL_WHITE,
        .timer_sel  = LEDC_TIMER,
        .duty       = 0,
        .hpoint     = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ccfg));

    ESP_LOGI(TAG,"pwm setup complete");

    /* mark init complete so subsequent calls become no‑ops. */
    s_initialized = true;
}

/**
 * @brief set white led brightness.
 *
 * @param level 8‑bit intensity value (0‑255); values outside this range are
 *              clamped internally.
 *
 * logs an error and returns if the driver has not yet been initialized.
 */

void led_set_white(uint8_t level)
{
    if (!s_initialized) {
        ESP_LOGE(TAG, "led driver not initialized");
        return;
    }

    /* convert the compile‑time resolution macro into a runtime max value. */
    uint32_t max_duty = (1 << PWM_RESOLUTION) - 1;
    /* clamp the caller‑supplied value so we never exceed the timer’s range. */
    if (level > max_duty) {
        level = max_duty;
    }

    /* write the new duty cycle to hardware and make it take effect. */
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_WHITE, level));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_WHITE));
}
