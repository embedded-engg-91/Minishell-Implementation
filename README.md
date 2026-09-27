# Minishell (msh)

A minimal Unix shell written in C, built using `fork()`/`execvp()`, signal handling, and a singly linked list for job tracking.

## Features Implemented

### Prompt

* Displays a shell prompt (`[minishell]$` by default).
* Prompt is customizable at runtime via `PS1=<value>` (no spaces around `=`).
* `PS1 = <value>` (with spaces) is **not** treated as a prompt change; it falls through and is handled as a regular (unrecognized) command.

### Command Execution

* Reads a line of input and identifies the command type: built-in, external, or invalid.
* External commands are validated against a whitelist (`external_cmds.txt`) before execution.
* Valid external commands are executed via `fork()` + `execvp()`, with the parent waiting for the child using `waitpid()`.
* Unrecognized commands print a `Command not found` message.

### Built-in Commands

* `cd <path>` — changes the current working directory.
* `pwd` — prints the current working directory.
* `exit` — terminates the shell.

### Special Variables

* `echo $?` — prints the exit/wait status of the last executed command.
* `echo $$` — prints the shell's own PID.
* `echo $SHELL` — prints the shell's working directory information.

### Signal Handling

* **Ctrl+C (SIGINT):** If a command is running in the foreground, the signal terminates that child process. If no foreground process is running, the shell simply redisplays the prompt.
* **Ctrl+Z (SIGTSTP):** Stops the foreground child process, prints its PID and process name, and records it as a background job.

### Job Control

* `jobs` — lists all currently stopped jobs.
* `fg` — resumes the most recently stopped job using `SIGCONT` and waits for it again.
* Stopped jobs are tracked internally using a singly linked list containing the PID and command name.

## Build

```bash
gcc msh.c scan_input.c get-cmd.c parse_input.c check_cmd.c \
    extract_externl_cmds.c execute_internal_cmds.c echo.c \
    signal_handler.c print_process_name.c sll_funs.c -o msh
```

Make sure `external_cmds.txt` is in the same directory as the executable. It is read at runtime to validate external commands.

## Run

```bash
./msh
```

## Project Structure

| File                      | Responsibility                                            |
| ------------------------- | --------------------------------------------------------- |
| `msh.c`                   | Entry point                                               |
| `scan_input.c`            | Main read-eval loop, signal setup, and fork/exec dispatch |
| `get-cmd.c`               | Extracts the command token from raw input                 |
| `parse_input.c`           | Tokenizes input into an `argv` array                      |
| `check_cmd.c`             | Classifies a command as built-in, external, or invalid    |
| `extract_externl_cmds.c`  | Loads the whitelist of allowed external commands          |
| `execute_internal_cmds.c` | Implements `cd`, `pwd`, `exit`, `fg`, and `jobs`          |
| `echo.c`                  | Implements `echo $?`, `echo $$`, and `echo $SHELL`        |
| `signal_handler.c`        | Handles SIGINT / SIGTSTP                                  |
| `print_process_name.c`    | Reads `/proc/<pid>/comm` to print a job's process name    |
| `sll_funs.c`              | Implements the singly linked list used for job tracking   |

```


