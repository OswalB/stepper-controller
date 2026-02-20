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

typedef enum
{
    PARSE_OK = 0,
    PARSE_ERR_INVALID_CMD,
    PARSE_ERR_INVALID_DOM,
    PARSE_ERR_ID_UNKNOW,
    PARSE_ERR_MANY_ARGS,
    PARSE_ERR_TOO_FEW_ARGS,
    PARSE_ERR_INVALID_PARAM,
    PARSE_ERR_INVALID_ID,
    PARSE_ERR_INVALID_FORMAT,
    PARSE_ERR_COUNT
} ParseResult;

// debe coincidir:
static const char *parse_error_str[PARSE_ERR_COUNT] =
    {
        "OK",
        "ERR COMMAND UNKNOWN",
        "ERR DOMAIN UNKNOWN",
        "ERR ID UNKNOWN",
        "ERR MANY ARGS",
        "ERR VALUEset",
        "ERR PARAM UNKNOWN",
        "ERR ID",
        "ERR FORMAT"};