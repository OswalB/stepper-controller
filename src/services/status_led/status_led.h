#pragma once

typedef enum {
    STATUS_LED_OFF = 0,
    STATUS_LED_IDLE,
    STATUS_LED_RUNNING,
    STATUS_LED_ERROR
} StatusLedState;

void status_led_init(void);
void status_led_set(StatusLedState state);
void status_led_update(void);
