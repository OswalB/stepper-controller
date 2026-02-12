#pragma once

typedef enum {
    STATUS_LED_OFF = 0,
    STATUS_LED_WARNING,
    STATUS_LED_ERROR,
    STATUS_LED_IDLE,
    STATUS_LED_RUNNING
} StatusLedState;


void status_leds_init(void);
void status_led_err_set(StatusLedState state);
void status_led_run_set(StatusLedState state);
void status_leds_update(void);
