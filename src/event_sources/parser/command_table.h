#pragma once

typedef void (*CommandHandler)(char *tokens[], int count); // alias puntero afuncion

typedef enum
{
    CMD_TYPE_ACTION,     // START MOTOR 0
    CMD_TYPE_SET         // SET MOTOR 2 SPEED 2300
} CommandType;


typedef struct // para construir la tabla de despacho basada en string
{
    const char *name;
    CommandHandler handler;
    CommandType type;
} CommandEntry;



extern const CommandEntry commandTable[];
extern const int commandCount;
