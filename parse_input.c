#include "msh.h"
void parse_input(char *input_string, char **argv)
{
    int index = 0;
    char *token = strtok(input_string, DELIMITERS);

    while (token != NULL && index < MAX_ARGS - 1)
    {
        argv[index++] = token;
        token = strtok(NULL, DELIMITERS);
    }

        argv[index] = NULL;
}