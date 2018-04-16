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
    "mkdir",
    "rmdir",
    "rm",
    "touch",
    "cat",
    "echo",
    NULL
};

// Verify how mane builtin commands we have and return this value
int num_cmds();

static int remove_all(const char *path, const struct stat *stat_buffer, int tflag, struct FTW *ftwbuffer);

/*
  Command functions declaration
 */

void command_pwd(char **args); // Show current directory
void command_exit(char **args); // Exit shell
void command_clear(char **args); // Clear the screen
void command_help(char **args); // Show helpful information
void command_ls(char **args); // Show all files and directories inside the working dir
void command_cd(char **args); // Change the working directory
void command_mkdir(char **args); // Create a new directory
void command_rmdir(char **args); // Remove a directory
void command_rm(char **args); // Remove a file
void command_touch(char **args); // Create a file
void command_cat(char **args); // Read a file and output their content
void command_echo(char **args); // Output a given string

// Execute process that aren't builtin
int shell_process(char **args);

// Execute the given command
void shell_execute(char **args);

// Initialize our basic loop
void shell_loop();

// Do some basic config, like set default working directory to /home/username
void shell_initialize();

#endif
