#include "esp_http_server.h"
#include "esp_log.h"
#include "led_driver.h"

static const char *TAG = "http";
static httpd_handle_t server = nullptr;

static esp_err_t root_handler(httpd_req_t *req)
{
    static const char resp[] = "smart bulb ok";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static esp_err_t on_handler(httpd_req_t *req)
{
    led_set_white(255);
    httpd_resp_sendstr(req,"{"state":"on"}");
    return ESP_OK;
}
static esp_err_t off_handler(httpd_req_t *req)
{
    led_set_white(0);
    httpd_resp_sendstr(req,"{"state":"off"}");
    return ESP_OK;
}
static esp_err_t brightness_handler(httpd_req_t *req)
{
    char buf[8];
    int level=128;
    if(httpd_req_get_url_query_str(req,buf,sizeof(buf))==ESP_OK){
        char val[4];
        if(httpd_query_key_value(buf,"v",val,sizeof(val))==ESP_OK){
            level = atoi(val);
            if(level<0) level=0;
            if(level>255) level=255;
        }
    }
    led_set_white(level);
    httpd_resp_sendstr(req,"{"ok":true}");
    return ESP_OK;
}

static void register_uri(httpd_handle_t s, const char* uri, esp_http_get_handler_t h)
{
    httpd_uri_t u = {.uri=uri,.method=HTTP_GET,.handler=h,.user_ctx=NULL};
    ESP_ERROR_CHECK(httpd_register_uri_handler(s,&u));
}

void http_server_start(void)
{
    httpd_config_t cfg = HTTPD_DEFAULT_CONFIG();
    cfg.server_port = 8080;
    ESP_ERROR_CHECK(httpd_start(&server,&cfg));
    register_uri(server,"/",root_handler);
    register_uri(server,"/api/on",on_handler);
    register_uri(server,"/api/off",off_handler);
    register_uri(server,"/api/brightness",brightness_handler);
    ESP_LOGI(TAG,"httpd on port %d",cfg.server_port);
}
