idf_component_register(
    SRCS "app_main.c" "wifi.c" "web_server.cpp" "led_driver.c"
    INCLUDE_DIRS "."
    REQUIRES driver esp_wifi esp_http_server esp_event esp_netif nvs_flash)
