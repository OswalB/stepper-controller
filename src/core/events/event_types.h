#pragma once
#include <stdint.h>
typedef enum
{
    EVT_NONE = 0,
    EVT_START,
    EVT_STOP,
    EVT_ERROR,
    EVT_RESET,
    EVT_MODE_SET,
    EVT_SET_SPEED
} EventType;

typedef struct
{
    EventType type; // Qué ocurrió
    uint8_t id;     // Quién lo generó / a quién aplica
    int32_t value;  // Dato asociado
} Event;
