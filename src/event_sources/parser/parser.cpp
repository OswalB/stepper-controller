#include "parser.h"
#include "command_table.h"
#include "./core/transport/transport.h"
#include <string.h>
#include <stdio.h>

#define MAX_TOKENS 8

// ----------------------------
// Helpers
// ----------------------------

ParseResult parser_validateStructure(CommandType type, int count)
{
    switch (type)
    {
        case CMD_TYPE_ACTION:
            // START MOTOR 0
            if (count != 3)
                return PARSE_ERR_TOO_FEW_ARGS;
            break;

        case CMD_TYPE_STATUS:
            // STATUS MOTOR 1
            if (count != 3)
                return PARSE_ERR_TOO_FEW_ARGS;
            break;

        case CMD_TYPE_SET:
            // SET MOTOR 2 SPEED 2300
            if (count != 5)
                return PARSE_ERR_TOO_FEW_ARGS;
            break;

        default:
            return PARSE_ERR_INVALID_FORMAT;
    }

    return PARSE_OK;
}

void parser_sendError(ParseResult err)
{
    switch (err)
    {
        case PARSE_ERR_TOO_FEW_ARGS:
            //Serial.println("ERR ARG");
            Transport_Send("ERR ARG");
            break;

        case PARSE_ERR_INVALID_ID:
            Transport_Send("ERR ID");
            break;

        case PARSE_ERR_INVALID_FORMAT:
            Transport_Send("ERR FORMAT");
            break;

        default:
            Transport_Send("ERR");
            break;
    }
}

// --------------------------------------------
// Tokenizador simple
// --------------------------------------------
static int tokenize(char *line, char *tokens[])
{
    int count = 0;

    char *token = strtok(line, " ");

    while (token != NULL && count < MAX_TOKENS)
    {
        tokens[count++] = token;
        token = strtok(NULL, " ");
    }

    return count;
}

// --------------------------------------------
// Parser principal
// --------------------------------------------
void parser_parse(char *line)
{
    char *tokens[MAX_TOKENS];
    int count = tokenize(line, tokens);

    if (count == 0)
        return;

    for (int i = 0; i < commandCount; i++)
    {
        if (strcmp(tokens[0], commandTable[i].name) == 0)
        {
            ParseResult r = parser_validateStructure(commandTable[i].type, count);

            if (r != PARSE_OK)
            {
                parser_sendError(r);
                return;
            }
            commandTable[i].handler(tokens, count);
            return;
        }
    }
    parser_sendError(PARSE_ERR_INVALID_FORMAT);
    
    /*No se encontró un comando en la tabla
    for (int i = 0; i < commandCount; i++)
    {
        if (strcmp("unknow", commandTable[i].name) == 0)
        {
            commandTable[i].handler(tokens, count);
            return;
        }
    }*/
}
