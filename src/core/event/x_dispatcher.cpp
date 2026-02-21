#include "x_dispatcher.h"
#include "core/event/event_types.h"
#include "core/event/event_queue.h"
#include "platform/transport/transport.h"
#include "input/command/command_table.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void dispatcher_sendError(ParseResult err);
long clamp(long value, long min, long max);
// -------------------------------------------------
// [SET]
// -------------------------------------------------

// [SET] / LED / PARAMS

void led_setDuty(long id, long value)
{
    value = clamp(value, 0, 100);

    Event ev;
    ev.type = EVT_SET_LED_DUTY;
    ev.id = id;
    ev.value = value;

    eventQueue_push(ev);
    Transport_Send(">>ok SET LED %02ld DUTY %ld ", id, value);
}

void led_setTime(long id, long value)
{
    value = clamp(value, 0, 60000);

    Event ev;
    ev.type = EVT_SET_LED_TIME;
    ev.id = id;
    ev.value = value;

    eventQueue_push(ev);
    Transport_Send(">>ok SET LED %02ld time %ld ", id, value);
}

// [SET] / LED / PARAMS / TABLE

static const LedSetEntry led_set_table[] =
    {
        {"DUTY", led_setDuty},
        {"TIME", led_setTime}};

#define LED_SET_COUNT (sizeof(led_set_table) / sizeof(led_set_table[0]))

void led_cmd_set(char *tokens[], int count)
{
    long id = strtol(tokens[2], NULL, 10);
    long value = strtol(tokens[4], NULL, 10);
    id = clamp(id, 0, 2);

    for (int i = 0; i < LED_SET_COUNT; i++)
    {
        if (strcmp(tokens[3], led_set_table[i].param) == 0)
        {
            led_set_table[i].handler(id, value);
            return;
        }
    }
    dispatcher_sendError(PARSE_ERR_INVALID_PARAM);
}

// [SET] / MOTOR / PARAMS

void motor_setAccel(long id, long value)
{
}

void motor_setSpeed(long id, long value)
{
    value = clamp(value, 0, 10000);
    Transport_Send(">>pendiente... SET MOTOR %02ld SPEED %ld ", id, value);
}

// [SET] / MOTOR / PARAMS / TABLE

static const MotorSetEntry motor_set_table[] =
    {
        {"SPEED", motor_setSpeed},
        {"ACCEL", motor_setAccel}};

#define MOTOR_SET_COUNT (sizeof(motor_set_table) / sizeof(motor_set_table[0]))

void motor_cmd_set(char *tokens[], int count)
{
    long id = strtol(tokens[2], NULL, 10);
    long value = strtol(tokens[4], NULL, 10);
    id = clamp(id, 0, 2);

    for (int i = 0; i < MOTOR_SET_COUNT; i++)
    {
        if (strcmp(tokens[3], motor_set_table[i].param) == 0)
        {
            motor_set_table[i].handler(id, value);
            return;
        }
    }
    dispatcher_sendError(PARSE_ERR_INVALID_PARAM);
}

// [SET] / DOMAINS / TABLE

static const SetDomainEntry set_domain_table[] =
    {
        {"MOTOR", motor_cmd_set},
        {"LED", led_cmd_set}};

#define SET_DOMAIN_COUNT (sizeof(set_domain_table) / sizeof(set_domain_table[0]))

void cmd_set(char *tokens[], int count)
{
    for (int i = 0; i < SET_DOMAIN_COUNT; i++)
    {
        if (strcmp(tokens[1], set_domain_table[i].domain) == 0)
        {
            set_domain_table[i].handler(tokens, count);
            return;
        }
    }
    dispatcher_sendError(PARSE_ERR_INVALID_DOM);
}

// -------------------------------------------------
// [START]
// -------------------------------------------------

void cmd_start(char *tokens[], int count) {}

// --------------------------------------------
// HELPERS
// --------------------------------------------

void dispatcher_sendError(ParseResult err)
{
    Transport_Send(">[CMMAND][DOMAIN][ID][PARAM][VALUE]");
    if (err < PARSE_ERR_COUNT)
    {
        Transport_Send(">>%s", parse_error_str[err]);
    }
    else
    {
        Transport_Send("ERR UNDEF");
    }
}

long clamp(long value, long min, long max)
{
    if (min > max)
    {
        long tmp = min;
        min = max;
        max = tmp;
    }

    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}