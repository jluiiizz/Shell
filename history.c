#include "history.h"

void save_on_history(char *command)
{
    char username[LOGIN_NAME_MAX];
    getlogin_r(username, sizeof(username)); // Get the username

    char history_path[MAXIMUN_DIR_LENGTH] = "/home/";
    strcat(history_path, username);
    strcat(history_path, "/.config/.jsh_history");

    FILE *history_file;
    history_file = fopen(history_path, "a");

    fprintf(history_file, "%s", command);

    fclose(history_file);
}
