#include "services/status_led/status_led.h"

void app_init() {
    status_leds_init();
    status_led_err_set(STATUS_LED_WARNING);// solo por probar
    status_led_run_set(STATUS_LED_RUNNING);
}