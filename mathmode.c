#include "mathmode.h"

char *read_input()
{
    char *line = NULL;
    size_t bufsize = 0;
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

// Maybe in the future, we need to refactor this code, changing **math__evaluate** from VOID to LONG LONG returning an
// long long to variable in MATH_LOOP and creating another function just to display the result, reducing the number
// of attribuitions to MATH_EVALUATE. BETTER CODE PRACTICE.
long double math_evaluate(char operations[], double values[])
{
    long double result = 0;
    int i;

    for (i = 0; i < input_count; i++) {
	if (operations[i] != 0) {
	    if (operations[i] == '+') {
		result += values[i - 1];
		result += values[i + 1];
	    } else if (operations[i] == '-') {
		result += values[i - 1];
		result -= values[i + 1];
	    } else if (operations[i] == '*') {
	    	result += values[i - 1];
	    	result *= values[i + 1];
	    } else if (operations[i] == '/') {
	    	result += values[i - 1];
	    	result = (result / values[i + 1]);
	    } else if (operations[i] == '%') {
	    	result += values[i - 1];
	    	result = ((int) result % (int) values[i + 1]);
	    }
	}
    }

    return result;
}

void math_loop()
{
    char *line;
    char **inputs;

    char math_operations[MAX_OPERATIONS];
    double math_numbers[MAX_VALUES];

    static int input_integrity = 1; // 1 is OK, 0 is an error

    do {
	printf(ANSI_LIGHT_CYAN " >> ");

	line = read_input();
	inputs = split_inputs(line);

	long double result;
	int i;
	input_count = count_strings(inputs);

	if (input_count > MAX_INPUT_NUMBER) { // *Temporary, i wanna focus first on make things work with a less number of arguments.
	    printf("MAX ARGUMENTS NUMBER is %d\n", MAX_INPUT_NUMBER);
	} else {
	    for (i = 0; i < input_count; i++) {
		if (contain_numbers_only(inputs[i]) == 1) {
		    math_numbers[i] = atof(inputs[i]);
		} else {
		    if (inputs[i][0] == '+') {
			math_operations[i] = '+';
		    } else if (inputs[i][0] == '-') {
			math_operations[i] = '-';
		    } else if (inputs[i][0] == '*') {
			math_operations[i] = '*';
		    } else if (inputs[i][0] == '/') {
			math_operations[i] = '/';
		    } else if (inputs[i][0] == '%') {
			math_operations[i] = '%';
		    }
		}
	    }

	    if (input_integrity == 1){
		result = math_evaluate(math_operations, math_numbers);
		printf("%.2Lf\n", result);
	    } else {
		printf(ANSI_LIGHT_RED "Some error occurred.");
	    }

	}

	free(line);
	free(inputs);
    } while (math_status != 1);
}
