#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_err.h"
void wifi_init(void);
void led_driver_init(void);
void http_server_start(void);
/**
 * @brief Application entry point.
 *
 * executes the startup sequence in the following order:
 *   1. non‑Volatile Storage (NVS)
 *   2. wifi subsystem
 *   3. led driver
 *   4. HTTP control server
 *
 * Each stage logs its progress and aborts on unrecoverable errors.
 */
static const char *TAG = "app_main";

void app_main(void)
{
    /* ---- initialise NVS ---- */
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "NVS partition truncated or incompatible; erasing and re‑initialising");
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    ESP_LOGI(TAG, "initializing wifi subsystem");
    wifi_init();
    ESP_LOGI(TAG, "initializing led driver");
    led_driver_init();
    ESP_LOGI(TAG, "launching HTTP control server");
    http_server_start();
    ESP_LOGI(TAG, "startup sequence complete");
}
