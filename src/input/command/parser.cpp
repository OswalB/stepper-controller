#include "parser.h"
#include "command_table.h"
#include "platform/transport/transport.h"
#include <string.h>
#include <stdio.h>
#include "lib/utils/utils.h"

#define MAX_TOKENS 5
/*


*/
// ----------------------------
// Helpers
// ----------------------------


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
            commandTable[i].handler(tokens, count);
            return;
        }
    }
    Transport_Send(">ERR CMMAND UNKNOW");
}
