#include "parser.h"
#include <string.h>
#include <stdio.h>

#include "lib/utils/utils.h"
#include "platform/transport/transport.h"
#include "core/command/command_resolver.h"
#include "core/event/event_builder.h"
#include "core/event/event_queue.h"

#define MAX_TOKENS 8
#define MAX_TOKEN_LENGTH 32

// --------------------------------------------
// Tokenizador simple
// --------------------------------------------
static int tokenize(const char *line, char tokens[][MAX_TOKEN_LENGTH])
{
    int count = 0;

    const char *ptr = line;

    while (*ptr != '\0' && count < MAX_TOKENS)
    {
        while (*ptr == ' ')
            ptr++;

        if (*ptr == '\0')
            break;

        int len = 0;
        while (*ptr != ' ' && *ptr != '\0' && len < MAX_TOKEN_LENGTH - 1)
        {
            tokens[count][len++] = *ptr++;
        }

        tokens[count][len] = '\0';
        count++;
    }

    return count;
}

// --------------------------------------------
// Parser principal
// --------------------------------------------
void parser_parse(const char *line)
{
    char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
    int token_count = tokenize(line, tokens);

    if (token_count == 0)
        return;

    for (int i = 0; i < token_count; i++)
    {
        if (!utils_is_numeric(tokens[i]))
        {
            utils_to_uppercase(tokens[i]);
        }
    }

    CommandMatch match;

    if (!command_resolve(tokens, token_count, &match))
    {
        Transport_Send("ERR: Unknown command\n");
        return;
    }

    Event event;

    if (!event_build_from_match(&match, &event))
    {
        Transport_Send("ERR: Cannot build event\n");
        return;
    }

    eventQueue_push(event);

    Transport_Send("event>%s >%s >%s >%s >%s", tokens[0],
                   tokens[1], tokens[2], tokens[3], tokens[4]);
    Transport_Send("ev dom>%d id>%d param>%d value>%ld",
               event.domain,
               event.id,
               event.param,
               event.value);
}
