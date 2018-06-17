#ifndef MATHMODE_H
#define MATHMODE_H

#define MAX_INPUT_NUMBER 7

#define INPUT_BUFFER_SIZE 64
#define INPUT_DELIMITERS " \t\r\n\a"

#define MAX_OPERATIONS 3 // Quantity of operations
#define MAX_VALUES 4

// char *operation[5]; // 0 means ADD, 1 means SUBTRACT
int math_operation[MAX_OPERATIONS]; // 0 means ADD, 1 means SUBTRACT
int math_numbers[MAX_VALUES]; // Given values

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
