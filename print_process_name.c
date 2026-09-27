#include "msh.h"
void print_process_name(pid_t pid)
{
    char path[50];
    char name[50];

    sprintf(path, "/proc/%d/comm", pid);

    FILE *fp = fopen(path, "r");

    if (fp != NULL)
    {
        fgets(name, sizeof(name), fp);
        printf("[%d] %s", pid, name);
        fclose(fp);
    }
}