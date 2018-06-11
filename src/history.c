#include "history.h"

void save_on_history(char *command)
{
    char *history_path = generate_absolute_path("/.config/.jsh_history");

    FILE *history_file;
    history_file = fopen(history_path, "a");

    fprintf(history_file, "%s", command);

    fclose(history_file);
}
