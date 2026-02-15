#include "parser.h"
#include "command_table.h"

#include <string.h>
#include <stdio.h>

#define MAX_TOKENS 8

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
            commandTable[i].handler(tokens, count);
            return;
        }
    }

    for (int i = 0; i < commandCount; i++)
    {
        if (strcmp("unknow", commandTable[i].name) == 0)
        {
            commandTable[i].handler(tokens, count);
            return;
        }
    }
}
