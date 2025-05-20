#include "esp_log.h"
#include "nvs_flash.h"
void wifi_init(void);
void led_driver_init(void);
void http_server_start(void);

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    wifi_init();
    led_driver_init();
    http_server_start();
}
