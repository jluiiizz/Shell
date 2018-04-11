#include "shell.h"

int num_cmds()
{
    return sizeof(commands)/sizeof(char*) - 1; // The -1 removes the NULL element from the list.
}

static int remove_all(const char *path, const struct stat *stat_buffer, int tflag, struct FTW *ftwbuffer)
{
    if (remove(path) != 0) {
	return -1;
    }
    return 0;
}

// This pointer point to the specific command function and pass the typed arguments.
void (*commands_ptr[]) (char**) = {
    &command_pwd,
    &command_exit,
    &command_clear,
    &command_help,
    &command_ls,
    &command_cd,
    &command_mkdir,
    &command_rmdir,
    &command_rm,
    &command_touch
};

void command_pwd(char **args)
{
    char path[MAX_DIR_LENGTH];
    getcwd(path, sizeof(path));
    printf("Current working directory: %s\n", path);
}

void command_exit(char **args)
{
    printf("EXITING ...\n");
    status = 1;
}

void command_clear(char **args)
{
    clear();
}

void command_help(char **args)
{
    int i;

    printf(ANSI_YELLOW "JShell - A simple shell built with C\n");
    printf(ANSI_YELLOW "Avaliable commands:\n\n");
    for (i = 0; i < num_cmds(); i++) {
	printf("%s\n", commands[i]);
    }
    printf(ANSI_YELLOW "\nThanks for using JShell. For more info please see github page -> https://github.com/jluiiizz/Shell\n");
}

void command_ls(char **args)
{
    char wdir[MAX_DIR_LENGTH];
    getcwd(wdir, sizeof(wdir)); // Get the current working directory

    DIR *dir;
    struct dirent *dire;
    struct stat stat_buffer;

    dir = opendir(wdir);

    if (args[1] != NULL) {
    	if (strcmp(args[1], "-l") == 0) {
    	    printf("\n");
    	    while ((dire=readdir(dir)) != NULL) {
		if (dire->d_name[0] != '.') {
		    if (stat(dire->d_name, &stat_buffer) == 0) {
			if (S_ISDIR(stat_buffer.st_mode) == 1) { // Means that is a directory
			    printf(ANSI_GREEN "%s\n" ANSI_NO_COLOR, dire->d_name);
			} else { // Means that is a regular file
			    printf(ANSI_CYAN "%s\n" ANSI_NO_COLOR, dire->d_name);
			}
		    }
		}
    	    }
    	} else if (strcmp(args[1], "-a") == 0) {
	    while ((dire=readdir(dir)) != NULL) {
    		if (stat(dire->d_name, &stat_buffer) == 0) {
		    if (S_ISDIR(stat_buffer.st_mode) == 1) {
			printf(ANSI_GREEN "%s " ANSI_NO_COLOR, dire->d_name);
		    } else {
			printf(ANSI_CYAN "%s " ANSI_NO_COLOR, dire->d_name);
		    }
		}
    	    }
	} else if (strcmp(args[1], "-la") == 0) {
    	    printf("\n");
    	    while ((dire=readdir(dir)) != NULL) {
		if (stat(dire->d_name, &stat_buffer) == 0) {
		    if (S_ISDIR(stat_buffer.st_mode) == 1) {
			printf(ANSI_GREEN "%s\n" ANSI_NO_COLOR, dire->d_name);
		    } else {
			printf(ANSI_CYAN "%s\n" ANSI_NO_COLOR, dire->d_name);
		    }
		}
    	    }
	}
    }

    while ((dire=readdir(dir)) != NULL) {
	if (dire->d_name[0] != '.') {
	    if (stat(dire->d_name, &stat_buffer) == 0) {
		if (S_ISDIR(stat_buffer.st_mode) == 1) {
		    printf(ANSI_GREEN "%s " ANSI_NO_COLOR, dire->d_name);
		} else {
		    printf(ANSI_CYAN "%s " ANSI_NO_COLOR, dire->d_name);
		}
	    }
	}
    }

    printf("\n");

    closedir(dir);
}

void command_cd(char **args)
{
    if (args[1] != NULL) {
	// Check if the given PATH is a file
	struct stat stat_buffer;
	char *path = args[1];
	if (stat(path, &stat_buffer) == 0) {
	    if (S_ISREG(stat_buffer.st_mode) == 1) {
		printf("Please type a VALID path.\n");
	    }
	}

	char wdir[MAX_DIR_LENGTH];
	getcwd(wdir, sizeof(wdir)); // Get the current working directory
	strcat(wdir, "/");
	strcat(wdir, args[1]);

	chdir(wdir);
    } else {
	printf("Please type a VALID path.\n");
    }
}

void command_mkdir(char **args)
{
    if (args[1] != NULL) {
	struct stat buffer;
	char *path = args[1];
	if (stat(path, &buffer) == 0) { // Verify target path existance.
	    printf("Already exist a directory with this name.\n");
	} else {
	    mkdir(path, 0777);
	}
    } else {
    	printf("Please type a VALID path.\n");
    }
}

void command_rmdir(char **args)
{
    if (args[1] != NULL) {
	if (strcmp(args[1], "--force") == 0) {
	    char *path = args[2];
	    struct stat *sbuf;
	    int tflags;
	    struct FTW *ftwb;
	    if (nftw(path, remove_all, 10, FTW_DEPTH | FTW_MOUNT | FTW_PHYS) == -1) {
		printf(ANSI_LIGHT_RED "Error: %s\n", strerror(errno));
	    } else {
		nftw(path, remove_all, 10, FTW_DEPTH | FTW_MOUNT | FTW_PHYS);
	    }
	} else {
	    char *path = args[1];

	    if (rmdir(path) == -1) {
		printf(ANSI_LIGHT_RED "Error: %s\n", strerror(errno));
	    } else {
		rmdir(path);
	    }
	}
    } else {
	printf("Please type a VALID path.\n");
    }
}

void command_rm(char **args)
{
    if (args[1] != NULL) {
	int i;
    	if (unlink(args[1]) == -1) { // Catch errors.
    	    printf(ANSI_LIGHT_RED "Error: %s\n", strerror(errno));
    	} else {
	    for (i = 0; args[i] != NULL; i++) {
		unlink(args[i]); // Remove the given files.
	    }
	}
    } else {
    	printf("Please type a VALID path.\n");
    }
}

void command_touch(char **args)
{
    if (args[1] != NULL) {
	char *path = args[1];
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (creat(path, mode) == -1) {
    	    printf(ANSI_LIGHT_RED "Error: %s\n", strerror(errno));
	} else {
	    creat(path, mode);
	}
    } else {
    	printf("Please type a VALID path.\n");
    }
}

void shell_execute(char **args)
{
    int i;

    if (args[0] != NULL) { // Verify if somethings was typed
	for (i = 0; i < num_cmds(); i++) { // Verify if typed command is equals to one of the available commands
	    if (strcmp(args[0], (char *) commands[i]) == 0) {
	        (*commands_ptr[i])(args);
		break;
	    } else if ((strcmp(args[0], (char *) commands[i]) != 0) && (check_string(args[0], commands) == 0)) { // If not, check if the typed command exist. Need this to tell the
		printf(ANSI_LIGHT_RED "Command not found. Avaliable commands: ");                                // correct message.
		int j;
		for (j = 0; j < num_cmds(); j++) {
		    if (j != (num_cmds() - 1)) {
			printf("%s, ", commands[j]);
		    } else {
			printf("%s. ", commands[j]);
		    }
		}
		printf("\n");
		break;
	    }
	}
    }
}

void shell_loop()
{
    char *line;
    char **args;

    // Get the username
    char username[LOGIN_NAME_MAX];
    getlogin_r(username, sizeof(username));

    do {
	char wdir[1024];
	getcwd(wdir, sizeof(wdir));
	printf(ANSI_LIGHT_GREEN "%s @ %s-> " ANSI_NO_COLOR, username, wdir);
	line = read_line(); // Read the given line.
	args = split_args(line); // Split all the word in arguments.
	shell_execute(args); // Execute the given command and their arguments.

	free(line);
	free(args);
    } while (status != 1);
}

void shell_initialize()
{
    char username[LOGIN_NAME_MAX];
    getlogin_r(username, sizeof(username)); // Get the username

    char wdir[MAX_DIR_LENGTH] = "/home/"; // Default working directory

    strcat(wdir, username);
    chdir(wdir);
}
