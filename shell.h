#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS_LENGTH 64
#define MAX_DIR_LENGTH 1024

// Represent the actual status of the shell
int status = 0; // 0 is running and 1 is closing

// Built-in commands
char *commands[] = {
    "pwd",
    "exit",
    "clear",
    "help",
    "ls",
    "cd",
    NULL
};

// Verify how mane builtin commands we have and return this value
int num_cmds();

/*
  Command functions declaration
 */

void command_pwd(char **args); // Show current directory
void command_exit(char **args); // Exit shell
void command_clear(char **args); // Clear the screen
void command_help(char **args); // Show helpful information
void command_ls(char **args); // Show all files and directorys inside the working dir
void command_cd(char **args); // Change the working directory

// Execute the given command
void shell_execute(char **args);

// Initialize our basic loop
void shell_loop();

// Do some basic config, like set default working directory to /home/username
void shell_initialize();

#endif
