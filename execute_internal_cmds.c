#include "msh.h"

extern pid_t pid;
void execute_internal_commands(char *input_string, Slist **head, int status)
{

    char *path;
    char *bkp;
    if (strncmp(input_string, "exit", 4) == 0)
    {
        exit(1);
    }

    if (strncmp(input_string, "pwd", 3) == 0)
    {
        system("pwd");
    }

    if (strncmp(input_string, "cd", 2) == 0)
    {

        path = strtok(input_string, " ");
        while (path != NULL)
        {
            bkp = path;
            path = strtok(NULL, " ");
        }
        chdir(bkp);
    }

    if (strncmp(input_string, "fg", 2) == 0)
    {

        if (sl_delete_last(head) == SUCCESS)
        {
            pid = backup_pid;

            kill(pid, SIGCONT);

            waitpid(pid, &status, WUNTRACED);

            if (WIFEXITED(status))
            {
                pid = 0;
            }
            else if (WIFSIGNALED(status))
            {
                pid = 0;
            }
            else if (WIFSTOPPED(status))
            {
                insert_at_last(head, pid, input_string);
                pid = 0;
            }
        }
    }

    if (strncmp(input_string, "jobs", 4) == 0)
    {
        print_list(*head);
    }
}
