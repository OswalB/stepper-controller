#include "parser.h"
#include "command_table.h"
#include "./core/transport/transport.h"
#include <string.h>
#include <stdio.h>
#include "../lib/utils/utils.h"

#define MAX_TOKENS 5
/*


*/
// ----------------------------
// Helpers
// ----------------------------
/*
bool parser_isValidDomain(const char *domain)
{
    if (strcmp(domain, "MOTOR") == 0)
        return true;
    if (strcmp(domain, "FAN") == 0)
        return true;
    if (strcmp(domain, "LED") == 0)
        return true;

    return false;
}

bool parser_isValidParam(const char *param)
{
    if (strcmp(param, "SPEED") == 0)
        return true;
    if (strcmp(param, "ACCEL") == 0)
        return true;
    if (strcmp(param, "MODE") == 0)
        return true;

    return false;
}

ParseResult parser_validateStructure(CommandType type, int count, char *tokens[])
{
    if (count < 2 || !parser_isValidDomain(tokens[1]))
        return PARSE_ERR_INVALID_DOM;

    switch (type)
    {
    case CMD_TYPE_ACTION:
        // START MOTOR 0
        if (count < 3)
            return PARSE_ERR_ID_UNKNOW;

        if (count > 3)
            return PARSE_ERR_MANY_ARGS;
        break;

    case CMD_TYPE_SET:
        // SET MOTOR 2 SPEED 2300
        if (!parser_isValidParam(tokens[3]))
            return PARSE_ERR_INVALID_PARAM;
        if (count != 5)
            return PARSE_ERR_TOO_FEW_ARGS;
        break;

    default:
        return PARSE_ERR_INVALID_FORMAT;
    }

    return PARSE_OK;
}


    */

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

    for (int i = 0; i < count; i++)
    {
        if (!utils_is_numeric(tokens[i]))
        {
            utils_to_uppercase(tokens[i]);
        }
    }

    for (int i = 0; i < commandCount; i++)
    {
        if (strcmp(tokens[0], commandTable[i].name) == 0)
        {
            /*ParseResult r = parser_validateStructure(commandTable[i].type, count, tokens);

            if (r != PARSE_OK)
            {
                parser_sendError(r);
                return;
            }*/
            commandTable[i].handler(tokens, count);
            return;
        }
    }
    Transport_Send(">ERR CMMAND UNKNOW");
}
