#include "dispatcher.h"
#include "core/events/event_types.h"
#include "core/events/event_queue.h"
#include "./core/transport/transport.h"
#include "command_table.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void dispatcher_sendError(ParseResult err);
long clamp(long value, long min, long max);
// -------------------------------------------------
// [SET] COMMAND
// -------------------------------------------------
// PARAMS

static void motor_setSpeed(long id, long value);
static void motor_setAccel(long id, long value);
static void motor_set_speed(long id, long value);

void motor_setSpeed(long id, long value)
{
    value = clamp(value, 0, 10000);
    Transport_Send(">>pendiente... SET MOTOR %02ld SPEED %ld ", id, value);
}

void motor_setAccel(long id, long value)
{
}

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

void led_cmd_set(char *tokens[], int count)
{
}

// DOMAIN

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

uint8_t GetCommandId(char **tokens, int count)
{
    if (count < 2)
        return 0;

    int value = atoi(tokens[1]);

    if (value < 0 || value > 255)
        return 0;

    return static_cast<uint8_t>(value);
}

// ----------------------------
// SET
// ----------------------------

void cmd_setXXXXXXX(char *tokens[], int count)
{
    int id = strtol(tokens[2], NULL, 10);
    long value = strtol(tokens[4], NULL, 10);

    Event ev;
    ev.type = EVT_ERROR;
    ev.id = id;
    ev.value = value;

    eventQueue_push(ev);

    Transport_Send(">OK %s %s %02d %s %ld ",
                   tokens[0], tokens[1], id, tokens[3], value);
}

// ----------------------------
// START
// ----------------------------

void cmd_start(char *tokens[], int count)
{
    uint8_t id = GetCommandId(tokens, count);

    // -------------------------------------------------
    // Si hay parámetro de velocidad → primero SET_SPEED
    // -------------------------------------------------
    if (count >= 3)
    {
        Event evSpeed;
        evSpeed.type = EVT_SET_SPEED;
        evSpeed.id = id;
        // evSpeed.paramType = PARAM_INT;   // puedes permitir float si quieres
        evSpeed.value = atol(tokens[2]);

        eventQueue_push(evSpeed);
        Transport_Send(">%s %u\r", "vel", evSpeed.value);
    }

    // -------------------------------------------------
    // Luego siempre EVT_START
    // -------------------------------------------------
    Event evStart;
    evStart.type = EVT_START;
    evStart.id = id;
    // evStart.paramType = PARAM_NONE;

    eventQueue_push(evStart);
    Transport_Send(">%s %u\r", "start", id);
}

void cmd_led(char *tokens[], int count)
{
    uint8_t id = GetCommandId(tokens, count);

    Event evStart;
    evStart.type = EVT_ERROR;
    evStart.id = id;
    // evStart.paramType = PARAM_NONE;

    eventQueue_push(evStart);
}

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