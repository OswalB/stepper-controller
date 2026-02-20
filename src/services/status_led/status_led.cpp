#include "status_led.h"
#include "led_pwm/led_pwm.h"

static LedPWM ledError(A0);
static LedPWM ledRun(A1);

void status_leds_init(void)
{
    ledError.init();
    status_led_err_set(ERR_LED_OFF);
    ledRun.init();
    status_led_run_set(RUN_LED_OFF);
}

void status_led_err_set(StatusLedErrState state)
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

void status_led_run_set(StatusLedRunState state)
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

void status_leds_update(void)
{
    ledError.update();
    ledRun.update();
}
