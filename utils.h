#ifndef UTILS_H
#define UTILS_H

// Defining color constants
#define ANSI_NO_COLOR "\033[0m"
#define ANSI_BLACK "\033[0;30m"
#define ANSI_RED "\033[0;31m"
#define ANSI_GREEN "\033[0;32m"
#define ANSI_BROWN "\033[0;33m"
#define ANSI_BLUE "\033[0;34m"
#define ANSI_PURPLE "\033[0;35m"
#define ANSI_CYAN "\033[0;36m"
#define ANSI_LIGHT_GRAY "\033[0;37m"
#define ANSI_DARK_GRAY "\033[1;30m"
#define ANSI_LIGHT_RED "\033[1;31m"
#define ANSI_LIGHT_GREEN "\033[1;32m"
#define ANSI_YELLOW "\033[1;33m"
#define ANSI_LIGHT_BLUE "\033[1;34m"
#define ANSI_LIGHT_PURPLE "\033[1;35m"
#define ANSI_LIGHT_CYAN "\033[1;36m"
#define ANSI_WHITE "\033[1;37m"

// Convert a value in bytes to megabytes
int convert_to_megabytes(unsigned long value_in_bytes);

// Convert a value in bytes to gigabytes
int convert_to_gigabytes(unsigned long value_in_bytes);

// Convert a low case string to UPPER CASE
void uppercase(char []);

// Convert a UPPER CASE string to low case
void lowcase(char []);

// Clear the screen
void clear_screen();

// Count number of strings inside an array. Its important to mention that the last element must be NULL for this function work
int count_strings(char *array_of_strings[]);

// Check if a string is inside and array of strings. 0 means there isn't the specific string in this array, 1 means the inverse
int check_string(char * my_string, char *array_of_strings[]);

// Check if the given path is a FILE. If the path is a directory it returns 0, if its a file return 1
int is_file(char *path);

// Verify if PATH is a dir. If the path is a directory it returns 1, if its a file return 0
int is_dir(char* path);

// Get the current working directory
char *get_cwdir();

// Return just the current folder name
char *get_fldrnm(char* path);

// Return the HOME path
char *get_home();

// Check the existance of a folder
int check_folder(char* path);

// Check the existance of a file
int check_file(char* path);

// Generate absolute path. 1 means succefull an -1 means failure
char *generate_absolute_path(char *path);

// Print a line break
void line_break();

// Check if a given string contain numbers only
int contain_numbers_only(char *string);

#endif
