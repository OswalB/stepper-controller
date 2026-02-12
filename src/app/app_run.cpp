#include "app_run.h"
#include "core/fsm/machine.h"
#include "services/status_led/status_led.h"
void app_run(){
    machine_update();
    status_leds_update();
}