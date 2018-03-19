#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS_LENGTH 64
#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

// Represent the actual status of the shell
int status = 0; // 0 is running and 1 is closing

// Read the line
char *read_line();

// Split the given line in the command and their arguments.
char **split_args(char *line);

// Initialize our basic loop.
void shell_loop();

#endif
