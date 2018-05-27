#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS_LENGTH 64
#define MAX_DIR_LENGTH 1024

// Represent the actual status of the shell
int status = 0; // 0 is running and 1 is closing

static mode_t file_creation_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

// Config folder path
static char *config_folder_path;
static char *config_file_path;
static char *log_file_path;
static char *history_file_path;

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
    "cp",
    "mv",
    "touch",
    "cat",
    "echo",
    "crusr",
    "clrhist",
    "home",
    "twitch",
    "math",
    NULL
};

// Verify how mane builtin commands we have and return this value
int num_cmds();

// Necessary function to use NFTW function on **--force** flag on **rmdir**
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
void command_cp(char **args); // Copy a file or a directory
void command_mv(char **args); // Move a file or a directory
void command_touch(char **args); // Create a file
void command_cat(char **args); // Read a file and output their content
void command_echo(char **args); // Output a given string
void command_crusr(char **args); // Print the current user
void command_clrhist(char **args); // Clear the history file (.config/jsh_history)
void command_home(char **args); // Print the home path
void command_twitch(char **args); // Show information about a twitch profile

void command_math(char **args); // Start the math mode

// Execute process that aren't builtin
void shell_process(char **args);

// Execute the given command
void shell_execute(char **args);

// Initialize our basic loop
void shell_loop();

// Generate config and log storage files, do some basic config, like set default working directory to /home/username
void shell_initialize();

#endif
