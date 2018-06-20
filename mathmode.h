#ifndef MATHMODE_H
#define MATHMODE_H

#define MAX_INPUT_NUMBER 7

#define INPUT_BUFFER_SIZE 64
#define INPUT_DELIMITERS " \t\r\n\a"

#define MAX_OPERATIONS 4 // Quantity of operations
#define MAX_VALUES 4

// char *operation[5]; //  means ADD, 2 means SUBTRACT
static int input_count;

// Represents the integrity of the inputs. 1 is OK, 0 is an error
static int input_integrity __attribute__ ((unused)) = 1;

// Represent the actual status of the math mode
int math_status = 0; // 0 is running and 1 is closing

// Read the inputs
char *read_inputs();

// Split every input into a string pointer
char **split_inputs(char *line);

// Evaluate the given expression
long long math_evaluate(char operations[], int values[]);

// Initialize our basic loop in MATH mode
void math_loop();

#endif
