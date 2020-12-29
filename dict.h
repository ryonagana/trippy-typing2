#ifndef DICT_H
#define DICT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct dictionary {
    char **words;
    int count;
}dictionary;


dictionary* dictionary_start(const char *filename);
void dictionary_info(dictionary *d);
char** dictionary_array_random_words(dictionary *dt, int count);
#endif // DICT_H
