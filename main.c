// Including C libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Including linux libraries (API)
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

// Include our own libraries and files
#include "utils.c"
#include "input.c"
#include "shell.c"

int main(int argc, char **argv)
{
    shell_initialize();
    shell_loop();

    return 0;
}
