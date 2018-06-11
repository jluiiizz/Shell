#include "input.h"

char *read_line()
{
    char *line = NULL;
    ssize_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

char **split_args(char *line)
{
    int bufsize = TOKEN_BUFFER_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    token = strtok(line, TOKEN_DELIMITERS);

    while (token != NULL) {
	tokens[position] = token;
	position++;

	if (position >= bufsize) {
	    bufsize += TOKEN_BUFFER_SIZE;
	    tokens = realloc(tokens, bufsize * sizeof(char*));
	    if (!tokens) {
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	    }
	}

	token = strtok(NULL, TOKEN_DELIMITERS);
    }

    tokens[position] = NULL;
    return tokens;
}
