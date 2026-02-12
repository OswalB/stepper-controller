#pragma once

typedef enum
{
    EVT_NONE = 0,
    EVT_START,
    EVT_STOP,
    EVT_ERROR,
    EVT_RESET
} EventType;

typedef struct
{
    EventType type;
} Event;


