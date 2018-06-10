#define _XOPEN_SOURCE 500
#define _GNU_SOURCE
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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <sys/wait.h>
#include <ctype.h>

// Including "non-oficial" libraries
#include <curl/curl.h>

// Include our own libraries and files
#include "utils.c"
#include "twitch.c"
#include "mathmode.c"
#include "history.c"
#include "input.c"
#include "shell.c"

int main(int argc, char **argv)
{
    shell_initialize();
    shell_loop();

    return 0;
}
