#include "services/status_led/status_led.h"
#include "core/events/event_queue.h"
#include "core/fsm/machine.h"
#include "event_sources/serial_if/serial_if.h"
#include "modules/motor/motor_config.h"

void app_init()
{
    eventQueue_init();
    status_leds_init();
    serial_init();
    machine_init();
    serial_writeln("=== SERIAL IF READY ===");

    motors_init();
}