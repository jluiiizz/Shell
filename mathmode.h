#ifndef MATHMODE_H
#define MATHMODE_H

#define MAX_INPUT_NUMBER 4

#define INPUT_BUFFER_SIZE 64
#define INPUT_DELIMITERS " \t\r\n\a"

// Represent the actual status of the math mode
int math_status = 0; // 0 is running and 1 is closing

// Read the inputs
char *read_inputs();

// Split every input into a string pointer
char **split_inputs(char *line);

// Evaluate the given expression
void math_evaluate(char **inputs);

// Initialize our basic loop in MATH mode
void math_loop();

#endif
