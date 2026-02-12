#include "status_led.h"
#include "led_pwm/led_pwm.h"

static LedPWM ledError(A0);
static LedPWM ledRun(A1);

void status_leds_init(void) {
    ledError.init();
    status_led_err_set(STATUS_LED_OFF);
    ledRun.init();
    status_led_run_set(STATUS_LED_OFF);
}

void status_led_err_set(StatusLedState state) {

    switch (state) {
        case STATUS_LED_OFF:
            ledError.set(0, 0);
            break;

        case STATUS_LED_WARNING:
            ledError.set(0.5f, 0.6f);
            break;

        case STATUS_LED_ERROR:
            ledError.set(6.0f, 0.2f);
            break;
    }
}

void status_led_run_set(StatusLedState state) {

    switch (state) {
        case STATUS_LED_OFF:
            ledRun.set(0, 0);
            break;

        case STATUS_LED_IDLE:
            ledRun.set(1.0f, 0.1f);
            break;

        case STATUS_LED_RUNNING:
            ledRun.set(1.0f, 0.5f);
            break;

    }
}

void status_leds_update(void) {
    ledError.update();
    ledRun.update();
}
