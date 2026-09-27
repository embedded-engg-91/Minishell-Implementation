#include "msh.h"
void echo(char *input_string, int status)
{

    if (strncmp(input_string, "echo $?", 7) == 0)
    {
        printf("%d\n", status);
    }

    if (strncmp(input_string, "echo $$", 7) == 0)
    {
        printf("%d\n", getpid());
    }

    if (strncmp(input_string, "echo $SHELL", 11) == 0)
    {

        system("pwd");
    }
}