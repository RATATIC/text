/*
* @file main.c
* @author Renat Kagal <kagal@itspartner.net>
*
* Assembling : gcc -Wall main.c -o main
*
* Description : program find words with yours characters, reverse text and counting sentensces and words in each sentence
*
* Copyright (c) 2021, ITS Partner LLC.
* All rights reserved.
*
* This software is the confidential and proprietary information of
* ITS Partner LLC. ("Confidential Information"). You shall not
* disclose such Confidential Information and shall use it only in
* accordance with the terms of the license agreement you entered into
* with ITS Partner.
*/

#include "head.h"

#define SIZE_READDING_CHAR 50
#define MAX_WORD_SIZE 20

#define SWAP(a, b)  ({\
                        typeof(a) tmp = a; \
                        a = b; \
                        b = tmp; \
                    })

static char* marks_between_words = {".,!? \'\""};
static char* punctuation_marks = {".?!"};

int main (int argc, char** argv) {
    char* path_text_file;
    char* path_to_output_file;
    char* text = (char*)malloc (sizeof (char) );
    char file_word[SIZE_READDING_CHAR];

    if (argc < 2){
        path_text_file = "text.txt";
        path_to_output_file = "outfile.txt";
    }
    else if (argc < 3){
        path_text_file = argv[1];
        path_to_output_file = "outfile.txt";
    }
    else {
        path_text_file = argv[1];
        path_to_output_file = argv[2];
    }

    FILE* fp;
    if ( (fp = fopen (path_text_file, "rt")) == NULL ) {
        puts ("Failed opennig file");
        exit(EXIT_FAILURE);
    }
    while ((fscanf (fp, "%s", file_word)) != EOF) {
        strcat(file_word, " ");
        text = realloc (text, (strlen(text) + strlen(file_word) + 1) * sizeof(char));
        strcat(text, file_word);
    }

    if (fclose(fp)) {
        puts("Failed closing file");
        exit(EXIT_FAILURE);
    }

    printf ("%s\n\n", text);

    char characters[MAX_WORD_SIZE];
    printf("Enter characters for searching : ");
    scanf ("%s", characters);

    if (strpbrk (marks_between_words, characters) != NULL || characters == NULL){
        printf("Bad characters : %s\n", characters);
    }
    else if (find_word (text, characters) == -1)
            printf ("Dont find this word in yours characters : %s\n", characters);
    
    char* r_text = strdup (text);
    reverse_sentence (r_text);

    FILE* fp2;
    if ( (fp2 = fopen (path_to_output_file, "wt")) == NULL ) {
        puts ("Failed opennig file");
        exit(EXIT_FAILURE);
    }

    fprintf(fp2, "%s", r_text);

    if (fclose(fp2)) {
        puts("Failed closing file");
        exit(EXIT_FAILURE);
    }

    printf("\n%s\n\n\n%s\n\n", r_text, text);

    counting_words_sentences (text);

    free (r_text);
    free (text);
}

//Function find word with characters and return count words with characters or -1 if doesnt find words with charactes 
int find_word (char* text, char* characters) {
    int count = -1;
    char* copy_text = text;

    if ((copy_text =  strstr (text, characters)) == NULL)
        return count;
    count = 0;

    while(copy_text != NULL) {
        copy_text = find_begin_of_word (copy_text, text);
        print_word (copy_text);

        copy_text = strstr (strpbrk (copy_text, marks_between_words), characters);
        ++count;
    }
    return count;
}

// Function reverse sentence and words in this sentence 
void reverse_sentence (char* text) {
    char* mark_ptr1 = text;
    char* mark_ptr2 ;

    while ( (mark_ptr2 = strpbrk (mark_ptr1, punctuation_marks)) != NULL) {
        for (int i = 0; i < (mark_ptr2 - mark_ptr1) / 2; i++) {
            SWAP (mark_ptr1[i], *(mark_ptr2 - i - 1));
        }
        mark_ptr1 = mark_ptr2 + 1;
    }
}

// Function counting words and sentences in the text
void counting_words_sentences (char* text) {
    char* mark_ptr1 = text;
    char* mark_ptr2;

    size_t count_sentences = 0;
    size_t count_words = 0;

    while ( (mark_ptr2 = strpbrk (mark_ptr1, punctuation_marks)) != NULL) {
        ++count_sentences;

        while (mark_ptr1 != (mark_ptr2)) {
            if (strchr(marks_between_words, mark_ptr1[1]) != NULL && strchr(marks_between_words, mark_ptr1[0]) == NULL) {
                ++count_words;
            }
            mark_ptr1++;
        }
        
        printf ("In %lds sentence %ld words\n", count_sentences, count_words);
        count_words = 0;
        mark_ptr1++;
    }
    printf ("Count of sentences : %ld\n", count_sentences);
}
//Function return a begin of the word 
char* find_begin_of_word (char* copy_text, char* text) {
    while (strchr (marks_between_words, copy_text[0]) == NULL && copy_text != (text - 1)) {
        --copy_text;
    }
    ++copy_text;

    return copy_text;
}
// Function print word 
void print_word (char* text) {
    size_t word_size = strpbrk (text, marks_between_words) - text;

    for (int i = 0; i < word_size; i++) {
        printf("%c", text[i]);
    }
    printf("\n");
}

/*
Написать программу, которая читает из текстового файла(путь к нему передается как аргумент при запуске) некоторый текст, выводит его на экран.
Реализовать алгоритм поиска для поиска всех слов в тексте, совпадающих с определенной последовательностью (вводим с клавиатуры).
Далее переворачиваеет каждое предложение(последнее слово становится первым и тд) в исходном тексте и каждое слово в предложении, сохраняя 
порядок предложенй, и выводит на экран результат.
Также вывести кол-во предложений в тексте и слов в каждом предложении.
*/
