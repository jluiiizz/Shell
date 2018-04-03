#include "shell.h"

int num_cmds()
{
    return sizeof(commands)/sizeof(char*) - 1; // The -1 removes the NULL element from the list.
}

// This pointer point to the specific command function and pass the typed arguments.
void (*commands_ptr[]) (char**) = {
    &command_pwd,
    &command_exit,
    &command_clear,
    &command_help,
    &command_ls,
    &command_cd,
    &command_mkdir
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
    printf("JShell - A simple shell built with C\n");
    printf("Avaliable commands:\n\n");
    for (i = 0; i < num_cmds(); i++) {
	printf("%s\n", commands[i]);
    }
    printf("\nThanks for using JShell. For more info please see github page -> https://github.com/jluiiizz/Shell\n");
}

void command_ls(char **args)
{
    char wdir[MAX_DIR_LENGTH];
    getcwd(wdir, sizeof(wdir)); // Get the current working directory
    unsigned char isFile = 0x8;
    unsigned char isDirectory = 0x4;

    DIR *dir;
    struct dirent *dire;

    dir = opendir(wdir);

    if (args[1] != NULL) {
	if (strcmp(args[1], "-l") == 0) {
	    printf("\n");
	    while ((dire=readdir(dir)) != NULL) {
		if (dire->d_type == isFile) {
		    printf("%s\n", dire->d_name);
		} else if (dire->d_type == isDirectory) {
		    printf(ANSI_GREEN "%s\n" ANSI_NO_COLOR, dire->d_name);
		} else {
		    printf("\n\nSOME ERROR\n\n");
		}
	    }
	}
    }

    while ((dire=readdir(dir)) != NULL) {
	if (dire->d_type == isFile) {
	    printf("%s ", dire->d_name);
	} else if (dire->d_type == isDirectory) {
	    printf(ANSI_GREEN"*%s " ANSI_NO_COLOR, dire->d_name);
	} else {
	    printf("\n\nSOME ERROR\n\n");
	}
    }

    printf("\n");

    closedir(dir);
}

void command_cd(char **args)
{
    if (args[1] != NULL) {
	char wdir[MAX_DIR_LENGTH];
	getcwd(wdir, sizeof(wdir)); // Get the current working directory

	strcat(wdir, "/");
	strcat(wdir, args[1]);

	chdir(wdir);
    } else {
	printf("Por favor digite um PATH valido!");
    }
}

void command_mkdir(char **args)
{
    struct stat buffer;
    char *path = args[1];
    if (path != NULL) {
	if (stat(path, &buffer) == 0) {
	    printf("Ja existe um diretorio com este nome.\n");
	} else {
	    mkdir(path, 0777);
	}
    } else {
    	printf("E necessario um caminho VALIDO.");
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
		printf("Command not found. Avaliable commands: ");                                               // correct message.
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
	printf("%s @ %s-> ", username, wdir);
	line = read_line(); // Read the given line.
	args = split_args(line); // Split all the word in arguments.
	shell_execute(args); // Execute the given command and their arguments.

	free(line);
	free(args);
    } while (status != 1);
}

void shell_initialize()
{
    char hostname[HOST_NAME_MAX];
    gethostname(hostname, sizeof(hostname)); // Get the hostname
    char username[LOGIN_NAME_MAX];
    getlogin_r(username, sizeof(username)); // Get the username

    char wdir[1024] = "/home/"; // Default working directory

    strcat(wdir, username);
    chdir(wdir);
}
