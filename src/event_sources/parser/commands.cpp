#include "commands.h"
#include "core/events/event_types.h"
#include "core/events/event_queue.h"
#include "./core/transport/transport.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*

bool parser_isValidId(const char *token, uint8_t maxId)
{
    for (int i = 0; token[i] != '\0'; i++)
    {
        if (!isdigit(token[i]))
            return false;
    }

    int id = atoi(token);

    if (id < 0 || id >= maxId)
        return false;

    return true;
}*/

/*static bool isFloat(const char *str)
{
    while (*str)
    {
        if (*str == '.')
            return true;
        str++;
    }
    return false;
}

static RunMode parseMode(const char *str)
{
    if (strcmp(str, "jog") == 0)
        return MODE_JOG;
    if (strcmp(str, "pasos") == 0)
        return MODE_PASOS;
    if (strcmp(str, "timer") == 0)
        return MODE_TIMER;
    if (strcmp(str, "pos") == 0)
        return MODE_POS;
    return MODE_NONE;
}*/

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

void cmd_set(char *tokens[], int count)
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
