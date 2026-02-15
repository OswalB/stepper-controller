#pragma once

typedef enum
{
    ERR_LED_OFF,
    ERR_LED_WARNING,
    ERR_LED_ERROR
} StatusLedErrState;

typedef enum
{
    RUN_LED_OFF,
    RUN_LED_IDLE,
    RUN_LED_RUNNING
} StatusLedRunState;

void status_leds_init(void);
void status_led_err_set(StatusLedErrState state);
void status_led_run_set(StatusLedRunState state);
void status_leds_update(void);
