#include "mathmode.h"

char *read_input()
{
    char *line = NULL;
    ssize_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

char **split_inputs(char *line)
{
    int bufsize = INPUT_BUFFER_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    token = strtok(line, INPUT_DELIMITERS);

    while (token != NULL) {
	tokens[position] = token;
	position++;

	if (position >= bufsize) {
	    bufsize += INPUT_BUFFER_SIZE;
	    tokens = realloc(tokens, bufsize * sizeof(char*));
	    if (!tokens) {
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	    }
	}

	token = strtok(NULL, INPUT_DELIMITERS);
    }

    tokens[position] = NULL;
    return tokens;
}

void math_evaluate(char **inputs)
{
    printf("OK!\n");
}

void math_loop()
{
    char *line;
    char **inputs;

    do {
	printf(ANSI_LIGHT_CYAN " >> ");

	line = read_input();
	inputs = split_inputs(line);
	math_evaluate(inputs);

	free(line);
	free(inputs);
    } while (math_status != 1);
}
