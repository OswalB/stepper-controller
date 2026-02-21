#include "x_command_table.h"

// Declaracion de handlers
void cmd_set(char *tokens[], int count);
// void cmd_status(char *tokens[], int count);
void cmd_start(char *tokens[], int count);
// void cmd_stop(char *tokens[], int count);
void cmd_led(char *tokens[], int count);
void cmd_unknow(char *tokens[], int count);

// Tabla de nombres de comandos

const CommandEntry commandTable[] =
    {
        {"SET", cmd_set, CMD_TYPE_SET},
        //{"STATUS", cmd_status, CMD_TYPE_STATUS},
        {"START", cmd_start, CMD_TYPE_ACTION}};
//{"STOP", cmd_stop, CMD_TYPE_ACTION}};

const int commandCount =
    sizeof(commandTable) / sizeof(CommandEntry);
