#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_word (char* word, char* file_text);

void print_word (char* word);

char* find_begin_of_word (char* word_ptr);