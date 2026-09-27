#include "msh.h"

int check_command_type(char *command)
{
    char *builtins[] = {"alias", "bg", "bind", "builtin", "case", "cd", "command", "compgen", "complete", "declare", "dirs",
                        "disown", "echo", "enable", "eval", "exec", "exit", "export", "fc", "fg", "getopts", "hash", "help", "history", "if", "jobs", "kill", "let", "local", "logout", "popd", "pushd", "pwd",
                        "read", "readonly", "set", "shift", "shopt", "source", "suspend", "test", "times", "trap", "type", "typeset", "ulimit", "umask", "unalias", "unset", "until", "wait", NULL};

    if (strcmp(command, "\n") == 0)
    {
        return NO_COMMAND;
    }

    for (int i = 0; builtins[i] != NULL; i++)
    {
        if (strcmp(command, builtins[i]) == 0)
        {
            return BUILTIN;
        }
    }

    char *external_cmds[155] = {NULL};
    extract_external_commands(external_cmds);
    for (int i = 0; external_cmds[i] != NULL; i++)
    {
        if (strcmp(command, external_cmds[i]) == 0)
        {
            return EXTERNAL;
        }
    }
    return INVALID;
}
