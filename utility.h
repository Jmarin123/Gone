#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <string.h>
int ends_with(const char *str, const char *suffix);

int file_to_string(const char *file);
#endif