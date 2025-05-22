#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file led_driver.h
 * @brief public api for the smart‑bulb led pwm driver.
 *
 * the module exposes a minimal interface:
 *   * `led_driver_init` — one‑time set‑up for timer and channel.
 *   * `led_set_white`   — 8‑bit brightness control for the white led.
 *
 * all comments follow lowercase style for consistency across the codebase.
 */

/**
 * @brief initialize the led pwm driver.
 */
void led_driver_init(void);

/**
 * @brief set white led brightness.
 *
 * @param level intensity 0‑255.
 */
void led_set_white(uint8_t level);

#ifdef __cplusplus
}
#endif