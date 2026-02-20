#pragma once




// -------------------------------------------------
// [SET] COMMAND 
// -------------------------------------------------


typedef void (*SetParamHandler)(long id, long value);

typedef struct
{
    const char *param;
    SetParamHandler handler;
} MotorSetEntry;

typedef struct
{
    const char *domain;
    void (*handler)(char *tokens[], int count);
} SetDomainEntry;



// API publica
void cmd_start(char *tokens[], int count);
void cmd_set(char *tokens[], int count);
