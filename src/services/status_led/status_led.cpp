#include "status_led.h"
#include "led_pwm/led_pwm.h"

static LedPWM ledError(13);
static StatusLedState currentState = STATUS_LED_OFF;

void status_led_init(void) {
    ledError.init();
    status_led_set(STATUS_LED_OFF);
}

void status_led_set(StatusLedState state) {
    currentState = state;

    switch (state) {
        case STATUS_LED_OFF:
            ledError.set(0, 0);
            break;

        case STATUS_LED_IDLE:
            ledError.set(1.0f, 0.1f);
            break;

        case STATUS_LED_RUNNING:
            ledError.set(2.0f, 0.5f);
            break;

        case STATUS_LED_ERROR:
            ledError.set(4.0f, 0.5f);
            break;
    }
}

void status_led_update(void) {
    ledError.update();
}
