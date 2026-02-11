#include "app_run.h"
#include "services/status_led/status_led.h"
void app_run(){
    status_led_update();
}