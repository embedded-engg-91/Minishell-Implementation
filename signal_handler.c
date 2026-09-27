#include "msh.h"

extern pid_t pid;
void signal_handler(int sig_num)
{

    if (pid != 0)
    {

        if (sig_num == SIGINT)
        {
            kill(pid, SIGKILL);
        }
        else if (sig_num == SIGTSTP)
        {
            kill(pid, SIGTSTP);
            print_process_name(pid);
        }
    }
    else
    {
        write(1, "\n", 1);
    }
}
