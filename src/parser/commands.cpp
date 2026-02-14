#include "commands.h"
#include "core/events/event_types.h"
#include "core/events/event_queue.h"
#include "./core/transport/transport.h"
#include <stdlib.h>
#include <string.h>

// ----------------------------
// Helpers
// ----------------------------
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

// ----------------------------
// START
// ----------------------------

void cmd_start(char *tokens[], int count)
{
    uint8_t id = 0;

    if (count >= 2)
        id = atoi(tokens[1]);

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
    }

    // -------------------------------------------------
    // Luego siempre EVT_START
    // -------------------------------------------------
    Event evStart;
    evStart.type = EVT_START;
    evStart.id = id;
    // evStart.paramType = PARAM_NONE;

    eventQueue_push(evStart);
    Transport_Send("OK %s %u\n", "start", id);
}

void cmd_led(char *tokens[], int count)
{

    uint8_t id = 0;

    if (count >= 2)
        id = atoi(tokens[1]);

    Event evStart;
    evStart.type = EVT_ERROR;
    evStart.id = id;
    // evStart.paramType = PARAM_NONE;

    eventQueue_push(evStart);
}
