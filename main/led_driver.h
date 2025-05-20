#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

void led_driver_init(void);
void led_set_white(uint8_t level);        /* 0‑255 via ledc pwm */

#ifdef __cplusplus
}
#endif
