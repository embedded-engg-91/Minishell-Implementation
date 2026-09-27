#include "msh.h"

pid_t pid;

void scan_input(char *prompt, char *input_string)
{
    char *command;
    int status, retstatus;
    Slist *head = NULL;

    struct sigaction sa;

    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    signal(SIGTSTP, SIG_IGN);

    while (1)
    {
        printf(ANSI_COLOR_RED "[%s]$" ANSI_COLOR_RESET, prompt);

        fflush(stdout);

        memset(input_string, '\0', 25);

        if (scanf("%[^\n]", input_string) != 1)
        {
            if (errno == EINTR)
            {
                clearerr(stdin);
                continue;
            }

            if (ferror(stdin))
            {
                clearerr(stdin);
            }
            else
            {
                getchar();
            }
            continue;
        }

        getchar();

        if (strncmp("PS1=", input_string, 4) == 0)
        {
            if (isspace((int)input_string[4]) == 0)
            {
                strcpy(prompt, &input_string[4]);

                memset(input_string, '\0', 25);
                continue;
            }
        }

        command = get_command(input_string);
        int cmd_type = check_command_type(command);
#ifdef DEBUG

#endif

        if (cmd_type == EXTERNAL)
        {

            pid = fork();
            if (pid == -1)
            {
                perror("fork");
            }
            else if (pid == 0)
            {

                signal(SIGTSTP, SIG_DFL);

                char *argv[MAX_ARGS];

                parse_input(input_string, argv);

                if (argv[0] == NULL)
                {
                    exit(0);
                }
                execvp(argv[0], argv);

                perror("execvp");
                exit(1);
            }
            else
            {

                waitpid(pid, &status, WUNTRACED);

                if (WIFEXITED(status))
                {
                    printf("Child with PID: %d terminated normally\n", pid);
                    pid = 0;
                }
                else if (WIFSIGNALED(status))
                {
                    printf("\nChild Process with PID: %d terminated due to signal.\n", pid);
                    printf("Sig# : %d\n", WTERMSIG(status));
                    pid = 0;
                }
                else if (WIFSTOPPED(status))
                {
                    printf("\n[%d]  Stopped   %s\n", pid, input_string);

                    insert_at_last(&head, pid, input_string);
#ifdef DEBUG
                    print_list(head);
#endif
                    pid = 0;
                }
            }

            memset(input_string, '\0', 25);
        }

        echo(input_string, status);

        execute_internal_commands(input_string, &head, status);

        if ((cmd_type == INVALID))
        {
            printf("%s : Command not found\n", input_string);
        }
    }
}