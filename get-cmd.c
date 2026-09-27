#include "msh.h"

char *get_command(char *input_string)
{

    char *cmd = malloc(sizeof(char) * 25);

    int ind = 0;
    while (1)
    {
        if (*input_string == ' ' || *input_string == '\0')
        {
            break;
        }
        cmd[ind++] = *input_string;
        input_string++;
    }
    cmd[ind] = '\0';

    return cmd;
}