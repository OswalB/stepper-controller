#include "services/status_led/status_led.h"
#include "core/events/event_queue.h"
#include "core/fsm/machine.h"

void app_init()
{
    eventQueue_init();
    status_leds_init();
    machine_init();

    Event evt;
    evt.type = EVT_ERROR;
    eventQueue_push(evt);

    // status_led_err_set(ERR_LED_WARNING);// solo por probar
    // status_led_run_set(RUN_LED_RUNNING);
}