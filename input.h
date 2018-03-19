#ifndef INPUT_H
#define INPUT_H

#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

// Read the line
char *read_line();

// Split the given line in the command and their arguments.
char **split_args(char *line);

#endif
