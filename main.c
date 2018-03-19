// Including C libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

// Including linux libraries (API)
#include <unistd.h>
#include <limits.h>

// Include our own libraries and files
#include "utils.c"
#include "shell.c"

int main(int argc, char **argv)
{
    shell_loop();

    return 0;
}
