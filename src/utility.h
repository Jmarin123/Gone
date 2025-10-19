#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ends_with(const char *str, const char *suffix);

char *file_to_string(const char *file);
#endif