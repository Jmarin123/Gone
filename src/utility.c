#include "utility.h"

int ends_with(const char *str, const char *suffix) {
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}


char *file_to_string(const char *file) {
    FILE *f = fopen(file, "r");
    if (!f) {
        perror(file);
        return NULL;
    }
    char* buffer = 0;

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    if (length == -1) {
        perror("ftell");
        fclose(f);
        return NULL;
    }
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length + 1);

    if (!buffer) {
        perror("malloc");
        fclose(f);
        return NULL;
    }

    size_t read = fread(buffer, 1, length, f);
    buffer[read] = '\0';
    fclose(f);
    return buffer;
}
