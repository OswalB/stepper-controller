#include "app_run.h"
#include "core/fsm/machine.h"
#include "modules/status_led/status_led.h"
#include "input/serial/serial_if.h"
void app_run()
{
    serial_update();
    machine_update();
    status_leds_update();
}
