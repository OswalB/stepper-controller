#pragma once
#include "core/types/event_types.h"

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

void led_init(void);
void led_handleEvent(const Event &evt);

void led_err_set(StatusLedErrState state);
void led_run_set(StatusLedRunState state);
void led_update(void);
void led_set_duty(long id, long value);
