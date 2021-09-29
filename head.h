#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Function find word with characters and return count words with characters or -1 if doesnt find words with charactes 
int find_word (char* text, char* charecters);

// Function reverse sentence and words in this sentence 
void reverse_sentence (char* text);

// Function counting words and sentences in the text
void counting_words_sentences (char* text);

//Function return a begin of the word 
void print_word (char* word);

// Function print word 
char* find_begin_of_word (char* copy_text, char* text);