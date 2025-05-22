idf_component_register(
    SRCS "app_main.c" "wifi.c" "web_server.cpp" "led_driver.c"
    INCLUDE_DIRS "."
    REQUIRES driver esp_wifi esp_http_server esp_event esp_netif nvs_flash)

# component CMake configuration for smart bulb main app
# ---------------------------------------------------------------

# ---- Source files ------------------------------------------------
set(SRC_FILES
    app_main.c
    wifi.c
    web_server.cpp
    led_driver.c
)

# ---- component registration -------------------------------------
idf_component_register(
    SRCS          ${SRC_FILES}
    INCLUDE_DIRS  .
    REQUIRES
        driver
        esp_wifi
        esp_http_server
        esp_event
        esp_netif
        nvs_flash
)

# ---- compiler warnings ------------------------------------------
# promote most warnings to errors for higher code quality
target_compile_options(${COMPONENT_LIB} PRIVATE -Wall -Wextra -Werror)