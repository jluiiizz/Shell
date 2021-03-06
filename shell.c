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
    &command_cp,
    &command_mv,
    &command_touch,
    &command_cat,
    &command_echo,
    &command_crusr,
    &command_clrhist,
    &command_home,
    &command_math
};

void command_pwd(char **args)
{
    printf("Current working directory: %s\n", get_cwdir());
}

void command_exit(char **args)
{
    printf("EXITING ...\n");
    status = 1;
}

void command_clear(char **args)
{
    clear_screen();
}

void command_help(char **args)
{
    if (args[1] == NULL) {
	int i;

	printf(ANSI_YELLOW "JShell - A simple shell built with C\n");
	printf(ANSI_YELLOW "Avaliable Built-in commands:\n\n");
	for (i = 0; i < num_cmds(); i++) {
	    printf("%s\n", commands[i]);
	}
	printf(ANSI_YELLOW "\nThanks for using JShell. For more info please see github page -> https://github.com/jluiiizz/Shell\n");
    }
}

void command_ls(char **args)
{
    char wdir[MAX_DIR_LENGTH];
    getcwd(wdir, sizeof(wdir));

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
			    printf(ANSI_GREEN "(%li) %s\n" ANSI_NO_COLOR, (long) stat_buffer.st_size, dire->d_name);
			} else { // Means that is a regular file
			    printf(ANSI_CYAN "(%li) %s\n" ANSI_NO_COLOR, (long) stat_buffer.st_size, dire->d_name);
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
			printf(ANSI_GREEN "(%li) %s\n" ANSI_NO_COLOR, (long) stat_buffer.st_size, dire->d_name);
		    } else {
			printf(ANSI_CYAN "(%li) %s\n" ANSI_NO_COLOR, (long) stat_buffer.st_size, dire->d_name);
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

	char *wdir = get_cwdir();
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

void command_cp(char **args)
{
    char *path = args[1];
    char *new_path = args[2];

    if (is_file(path) == 1) {
    	int src, dest;
    	src = open(path, O_RDONLY);
    	dest = creat(new_path, file_creation_mode);

    	off_t bytes = 0;
    	struct stat stat_buffer;
    	fstat(src, &stat_buffer);
    	if (sendfile(dest, src, &bytes, stat_buffer.st_size) == -1) {
    	    printf(ANSI_LIGHT_RED "Error: %s\n", strerror(errno));
    	} else {
    	    sendfile(dest, src, &bytes, stat_buffer.st_size);
    	}
    } else {
    	printf(ANSI_LIGHT_RED "At least for now this command just work with files\n\n");
	return;
    }
}

void command_mv(char **args)
{
    char *old_path = args[1];
    char *new_path = args[2];

    if ((old_path != NULL) && (new_path != NULL)) {
	if (rename(old_path, new_path) == -1) {
    	    printf(ANSI_LIGHT_RED "Error: %s\n", strerror(errno));
	} else {
	    rename(old_path, new_path);
	}
    } else {
    	printf("Please type a VALID path.\n");
    }
}

void command_touch(char **args)
{
    if (args[1] != NULL) {
	char *path = args[1];
	if (creat(path, file_creation_mode) == -1) {
    	    printf(ANSI_LIGHT_RED "Error: %s\n", strerror(errno));
	} else {
	    creat(path, file_creation_mode);
	}
    } else {
    	printf("Please type a VALID path.\n");
    }
}

void command_cat(char **args)
{
    if (args[1] != NULL) {
    	char *path = args[1];
    	if (is_dir(path) == 1) { // Means that is a directory
	    printf(ANSI_LIGHT_RED "Not a file\n");
    	} else {
	    FILE *target;
	    target = fopen(path, "r"); // "r" means that we are just reading
	    int c;
	    if (target != NULL) {
		while ((c = getc(target)) != EOF) {
		    putchar(c);
		}
		fclose(target);
	    }
    	}
    } else {
    	printf("Please type a VALID path.\n");
    }
}

void command_echo(char **args)
{
    int i;
    for (i = 1; i < count_strings(args); i++) {
	printf("%s ", args[i]);
    }
    printf("\n");
}

void command_crusr(char **args)
{
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (pw == NULL) {
	printf("Error");
	return;
    } else {
	printf("%s", pw->pw_name);
    }
}

void command_clrhist(char **args)
{
    char confirmation;
    printf("Are you sure that you want to clear the history ? (y/n) : ");
    scanf("%c", &confirmation);
    if (confirmation == 'y') {
	unlink(history_file_path);
	creat(history_file_path, file_creation_mode);
	return;
    } else if (confirmation == 'n') {
	return;
    } else {
	printf(ANSI_LIGHT_RED "Invalid option.\n");
	return ;
    }
}

void command_home(char **args)
{
    printf("Home: %s\n", get_home());
}

void command_math(char **args)
{
    math_loop();
}

void shell_process(char **args)
{
    pid_t pid;
    pid_t opid __attribute__((unused));
    int process_status;

    pid = fork();
    if (pid == 0) {
	if (execvp(args[0], args) == -1) {
	    printf(ANSI_LIGHT_RED "Command not found. Avaliable commands: ");
	    int j;
	    for (j = 0; j < num_cmds(); j++) {
		if (j != (num_cmds() - 1)) {
		    printf("%s, ", commands[j]);
		} else {
		    printf("%s. ", commands[j]);
		}
	    }
	    printf("\n");
	}
	exit(EXIT_FAILURE);
    } else if (pid < 0) {
	perror(ANSI_LIGHT_RED "JShell");
    } else {
	do {
	    opid = waitpid(pid, &process_status, WUNTRACED);
	} while (!WIFEXITED(process_status) && !WIFSIGNALED(process_status));
    }
}

void shell_execute(char **args)
{
    int i;

    if (args[0] != NULL) { // Verify if somethings was typed
	for (i = 0; i < num_cmds(); i++) { // Verify if typed command is equals to one of the available commands
	    if (strcmp(args[0], (char *) commands[i]) == 0) {
	        (*commands_ptr[i])(args);
		return;
	    }
	}
	shell_process(args);
    }
}

void shell_loop()
{
    char *line;
    char **args;

    char *username = get_username();

    do {
	char wdir[MAX_DIR_LENGTH];
	getcwd(wdir, sizeof(wdir));
	char *crfldr = get_fldrnm(wdir); // Get just the last folder of the path name

	if (strcmp(crfldr, username) == 0) {
	    printf(ANSI_LIGHT_GREEN "~ -> " ANSI_NO_COLOR); // Compact PS1 style
	} else {
	    printf(ANSI_LIGHT_GREEN "%s -> " ANSI_NO_COLOR, crfldr); // Compact PS1 style
	}

	line = read_line(); // Read the given line.
	save_on_history(line); // Save line on history file
	args = split_args(line); // Split all the word in arguments.
	shell_execute(args); // Execute the given command and their arguments.

	free(line);
	free(args);
    } while (status != 1);
}

void shell_initialize()
{
    chdir(get_home()); // Set default working directory to /home/#{user}

    // Generate **config** folder and files

    config_folder_path = generate_absolute_path("/.config");
    config_file_path = generate_absolute_path("/.config/.jshrc");
    log_file_path = generate_absolute_path("/.config/.jsh_log");
    history_file_path = generate_absolute_path("/.config/.jsh_history");

    // Verify the existence of our configuration folder and file, log file and history file. And create new one if not exist.

    if (check_folder(config_folder_path) == 0) {
	mkdir(config_folder_path, 0777);
	if (check_file(config_file_path) == 0) {
	    creat(config_file_path, file_creation_mode);
	}
	if (check_file(log_file_path) == 0) {
	    creat(log_file_path, file_creation_mode);
	}
	if (check_file(history_file_path)) {
	    creat(history_file_path, file_creation_mode);
	}
    } else {
	if (check_file(config_file_path) == 0) {
	    creat(config_file_path, file_creation_mode);
	}
	if (check_file(log_file_path) == 0) {
	    creat(log_file_path, file_creation_mode);
	}
	if (check_file(history_file_path) == 0) {
	    creat(history_file_path, file_creation_mode);
	}
    }
}
