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
	    return 1;
	}
    }
    return 0;
}


int is_file(char *path)
{
    struct stat buffer;
    if (stat(path, &buffer) != 0) {
	return 0;
    } else {
	return S_ISDIR(buffer.st_mode);
    }
}
