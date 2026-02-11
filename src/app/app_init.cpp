#include "services/status_led/status_led.h"

void app_init() {
    status_led_init();
    status_led_set(STATUS_LED_IDLE);// solo por probar
}