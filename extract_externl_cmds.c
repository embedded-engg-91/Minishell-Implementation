#include "msh.h"

void extract_external_commands(char **external_commands)
{

    int fd, ind = 0, j = 0;
    char ch;
    char buffer[25] = {'\0'};

    fd = open("external_cmds.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    while (read(fd, &ch, 1) > 0)
    {
        if (ch == '\r')
        {
            continue;
        }
        if (ch != '\n')
        {
            buffer[ind++] = ch;
        }
        else
        {

            buffer[ind] = '\0';

            external_commands[j] = calloc(strlen(buffer) + 1, sizeof(char));

            strcpy(external_commands[j++], buffer);

            memset(buffer, '\0', 25);

            ind = 0;
        }
    }
#ifdef DEBUG
    for (int i = 0; external_commands[i] != NULL; i++)
    {
        printf("[%d] = <%s>\n", i, external_commands[i]);
    }
#endif
    close(fd);
}
