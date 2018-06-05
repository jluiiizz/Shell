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

// Maybe in the future, we need to refactor this code, changing math_evaluate from VOID to LONG LONG returning an
// long long to variable in MATH_LOOP and creating another function just to display the result, reducing the number
// of attribuitions to MATH_EVALUATE. BETTER CODE PRACTICE.

void math_evaluate(char **inputs)
{
    // long long result;

    int args_count = count_strings(inputs);
    int converted_inputs[args_count];
    int i;

    for (i = 0; i < count_strings(inputs); i++) // Walks through the **inputs** array
    {
	if (contain_numbers_only(inputs[i]) == 0) { // Verify if the given string can be converted to a number
	    printf(ANSI_LIGHT_RED "%s is not a number", inputs[i]);
	} else {
	    converted_inputs[i] = atoi(inputs[i]); // Convert the string into an integer and store it in a variable for future calc
	}
    }

    line_break();

    // printf("%lli", result);
}

void math_loop()
{
    char *line;
    char **inputs;

    do {
	printf(ANSI_LIGHT_CYAN " >> ");

	line = read_input();
	inputs = split_inputs(line);
	if (count_strings(inputs) > 4) { // Temporary, i wanna focus first on make things work with a less number of arguments.
	    printf("MAX ARGUMENTS NUMBER is 4\n");
	} else {
	    math_evaluate(inputs);
	}

	free(line);
	free(inputs);
    } while (math_status != 1);
}
