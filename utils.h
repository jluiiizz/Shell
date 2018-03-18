#ifndef UTILS_H
#define UTILS_H

// Convert a value in bytes to megabytes
int convert_to_megabytes(unsigned long value_in_bytes);

// Convert a value in bytes to gigabytes
int convert_to_gigabytes(unsigned long value_in_bytes);

// Convert a low case string to UPPER CASE
void uppercase(char []);

// Convert a UPPER CASE string to low case
void lowcase(char []);

// Clear the screen
void clear();

#end
