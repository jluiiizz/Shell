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
