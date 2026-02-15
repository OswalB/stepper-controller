#include "core/fsm/machine.h"
#include "core/events/event_queue.h"
#include "core/events/event_types.h"
#include "services/status_led/status_led.h"

typedef enum
{
    MS_IDLE = 0,
    MS_RUNNING,
    MS_ERROR
} MachineState;

static MachineState g_state;

void machine_init(void)
{
    g_state = MS_IDLE;
    status_led_run_set(RUN_LED_IDLE);
}

// Handler

/*EventResult*/ void machine_handleEvent(Event evt)
{
    if (evt.type == EVT_ERROR)
    {
        g_state = MS_ERROR;
        status_led_err_set(ERR_LED_ERROR);
        return;
    }

    switch (g_state)
    {
    case MS_IDLE:

        if (evt.type == EVT_START)
        {
            g_state = MS_RUNNING;
            status_led_run_set(RUN_LED_RUNNING);
        }

        break;

    case MS_RUNNING:

        if (evt.type == EVT_STOP)
        {
            g_state = MS_IDLE;
            status_led_run_set(RUN_LED_IDLE);
        }
        else if (evt.type == EVT_ERROR)
        {
            g_state = MS_ERROR;
            status_led_err_set(ERR_LED_ERROR);
        }

        break;

    case MS_ERROR:

        if (evt.type == EVT_RESET)
        {
            g_state = MS_IDLE;
            status_led_run_set(RUN_LED_IDLE);
        }

        break;
    }
}

void machine_update(void)
{
    Event evt;

    if (eventQueue_pop(&evt))
    {
        machine_handleEvent(evt);
    }
}
