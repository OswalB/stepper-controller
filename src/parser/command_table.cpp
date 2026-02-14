#include "command_table.h"

// Declaracion de handlers
void cmd_start(char* tokens[], int count);
void cmd_led(char* tokens[], int count);

// Tabla de nombres de comandos

const CommandEntry commandTable[] =
{
    { "start", cmd_start },
    { "er",  cmd_led  }
};

const int commandCount =
    sizeof(commandTable) / sizeof(CommandEntry);
