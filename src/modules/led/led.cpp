#include "led.h"
#include "drivers/led_pwm/led_pwm.h"
#include "platform/transport/transport.h"

static LedPWM ledError(A0);
static LedPWM ledRun(A1);
// static Led_State g_ledState;  en este caso no se usa

void led_init(void)
{
    ledError.init();
    led_err_set(ERR_LED_OFF);
    ledRun.init();
    led_run_set(RUN_LED_OFF);
}

void led_handleEvent(const Event &evt)
{
    Transport_Send("manejador de eventos>> %d ", evt.value);
}

void led_err_set(StatusLedErrState state)
{

    switch (state)
    {
    case ERR_LED_OFF:
        ledError.start_led(0, 0);
        break;

    case ERR_LED_WARNING:
        ledError.start_led(1000, 50);
        break;

    case ERR_LED_ERROR:
        ledError.start_led(200, 25);
        break;
    }
}

void led_run_set(StatusLedRunState state)
{

    switch (state)
    {
    case RUN_LED_OFF:
        ledRun.start_led(0, 0);
        break;

    case RUN_LED_IDLE:
        ledRun.start_led(3000, 10);
        break;

    case RUN_LED_RUNNING:
        ledRun.start_led(500, 50);
        break;
    }
}

void led_set_duty(long id, long value)
{
    switch (id)
    {
    case 0:
        ledError.set_duty((uint8_t)value);
        break;

    case 1:
        ledRun.set_duty((uint8_t)value);
        break;

    default:
        // opcional: error
        break;
    }
}

void led_update(void)
{
    ledError.update();
    ledRun.update();
}
