#pragma once

typedef void (*CommandHandler)(char *tokens[], int count); // alias puntero afuncion

typedef struct // para construir la tabla de despacho basada en string
{
    const char *name;
    CommandHandler handler;
} CommandEntry;

extern const CommandEntry commandTable[];
extern const int commandCount;
