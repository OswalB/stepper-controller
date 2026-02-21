#include "core/event/event_queue.h"
#include "modules/status_led/status_led.h"
#include "input/serial/serial_if.h"
#include "core/fsm/machine.h"
#include "modules/motor/motor.h"

void app_init()
{
    eventQueue_init();
    status_leds_init();
    serial_init();
    machine_init();
    serial_writeln("=== SERIAL IF READY ===");
    //motorSystem_init();
}