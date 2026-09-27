#ifndef MSH_H
#define MSH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define BUILTIN 1
#define EXTERNAL 2
#define NO_COMMAND 3
#define INVALID 4

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define SUCCESS 0
#define FAILURE -1
#define MAX_ARGS 64
#define DELIMITERS " \t\r\n"

typedef struct node
{
	pid_t pid;
	char p_name[50];
	struct node *link;
} Slist;

extern pid_t backup_pid;

int insert_at_last(Slist **head, pid_t, char *);
void print_list(Slist *head);

int sl_delete_last(Slist **head);

void scan_input(char *prompt, char *input_string);
void copy_change(char *prompt, char *input_string);
char *get_command(char *input_string);
void parse_input(char *input_string, char **argv);

int check_command_type(char *command);
void echo(char *input_string, int status);
void execute_internal_commands(char *input_string, Slist **head, int status);
void signal_handler(int sig_num);
void clear_tokens(char **tokens);
void print_process_name(pid_t pid);
void extract_external_commands(char **external_commands);
#endif
