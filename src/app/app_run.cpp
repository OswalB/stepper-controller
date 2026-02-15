#include "app_run.h"
#include "core/fsm/machine.h"
#include "services/status_led/status_led.h"
#include "event_sources/serial_if.h"
void app_run()
{
    serial_update();
    machine_update();
    status_leds_update();
}