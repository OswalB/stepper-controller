#pragma once

typedef void (*CommandHandler)(char *tokens[], int count); // alias puntero afuncion

typedef enum
{
    CMD_TYPE_ACTION,     // START MOTOR 0
    CMD_TYPE_STATUS,     // STATUS MOTOR 1
    CMD_TYPE_SET         // SET MOTOR 2 SPEED 2300
} CommandType;

typedef enum
{
    PARSE_OK = 0,
    PARSE_ERR_TOO_FEW_ARGS,
    PARSE_ERR_INVALID_ID,
    PARSE_ERR_INVALID_FORMAT,
    PARSE_ERR_INVALID_CMD,
    PARSE_ERR_INVALID_DOM,
    PARSE_ERR_ID_UNKNOW
} ParseResult;

typedef struct // para construir la tabla de despacho basada en string
{
    const char *name;
    CommandHandler handler;
    CommandType type;
} CommandEntry;



extern const CommandEntry commandTable[];
extern const int commandCount;
