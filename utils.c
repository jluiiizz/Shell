#include "utils.h"

int convert_to_megabytes(unsigned long valueInBytes)
{
    int valueInMegabytes = ((valueInBytes/1024)/1024);
    return valueInMegabytes;
}

int convert_to_gigabytes(unsigned long valueInBytes)
{
    int valueInGigabytes = (((valueInBytes/1024)/1024)/1024);
    return valueInGigabytes;
}

void uppercase(char s[])
{
   int c = 0;

   while (s[c] != '\0') {
      if (s[c] >= 'a' && s[c] <= 'z') {
         s[c] = s[c] - 32;
      }
      c++;
   }
}

void lowercase(char s[])
{
   int c = 0;

   while (s[c] != '\0') {
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }
}

void clear()
{
    printf("\033[H\033[J");
}

int count_strings(char *array_of_strings[])
{
    int count = 0, i;
    for (i = 0; array_of_strings[i] != NULL; i++) {
	count++;
    }
    return count;
}

int check_string(char *my_string, char *array_of_strings[])
{
    int i;
    int num_strings = count_strings(array_of_strings);

    for (i = 0; i < num_strings; i++) {
	if (strcmp(my_string, array_of_strings[i]) == 0) {
	    return 1; // my_string is inside of array_of_strings
	}
    }
    return 0; // my_string isn't inside of array_of_strings
}


int is_file(char *path)
{
    struct stat stat_buffer;
    if (stat(path, &stat_buffer) != 0) {
	printf(ANSI_LIGHT_RED "Error: %s\n", strerror(errno));
	return -1;
    } else {
	return S_ISREG(stat_buffer.st_mode);
    }
}

int is_dir(char *path)
{
    struct stat stat_buffer;
    if (stat(path, &stat_buffer) != 0) {
	printf(ANSI_LIGHT_RED "Error: %s\n", strerror(errno));
	return -1;
    } else {
	return S_ISDIR(stat_buffer.st_mode);
    }
}

char *get_cwdir()
{
    char wdir[1024];
    getcwd(wdir, sizeof(wdir));
    char *wdir_ptr = wdir;
    return wdir_ptr;
}

char *get_fldrnm(char *path)
{
    char *token;
    char *directory;
    size_t length;

    token = strrchr(path, '/');

    length = strlen(token);
    directory = malloc(length);
    memcpy(directory, token+1, length);

    return directory;
}

char *get_home()
{
    char *username = getlogin();
    char *start_home = "/home/";

    char *home = malloc(strlen(username) + strlen(start_home) + 1);
    strcpy(home, start_home);
    strcat(home, username);

    return home;
}

int check_folder(char* path)
{
    struct stat stat_buffer;
    if ((stat(path, &stat_buffer) == 0) && (S_ISDIR(stat_buffer.st_mode) == 1)) {
	return 1; // The given folder exist
    } else {
	return 0; // The given folder don't exist
    }
}

int check_file(char* path)
{
    struct stat stat_buffer;
    if ((stat(path, &stat_buffer) == 0) && (S_ISREG(stat_buffer.st_mode) == 1)) {
	return 1; // The given file exist
    } else {
	return 0; // The given file don't exist
    }
}

char *generate_absolute_path(char *path)
{
    char *abs_path = malloc(sizeof(char) * 512);
    strcpy(abs_path, get_home());
    strcat(abs_path, path);

    return abs_path;
}
