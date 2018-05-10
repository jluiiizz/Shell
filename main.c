#define _XOPEN_SOURCE 500
// Including C libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Including linux libraries (API)
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <ftw.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

// Include our own libraries and files
#include "utils.c"
#include "history.c"
#include "input.c"
#include "shell.c"

int main(int argc, char **argv)
{
    shell_initialize();
    shell_loop();

    return 0;
}
