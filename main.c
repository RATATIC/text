/*
* @file main.c
* @author Renat Kagal <kagal@itspartner.net>
*
* Assembling : gcc main.c -o main
*
* Description :
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

static char* punctuation_marks = {".,!? \'\"-"};

int main (int argc, char** argv) {
	char* path_text_file;
	char* text = "";
	char file_word[SIZE_READDING_CHAR];


	if (argc < 2)
		path_text_file = "text.txt";
	else
		path_text_file = argv[1];

	FILE* fp;
	if ( (fp = fopen (path_text_file, "rt")) == NULL ) {
		puts ("Failed opennig file");
		exit(EXIT_FAILURE);
	}
	while ((fscanf (fp, "%s", file_word)) != EOF) {
		if ( asprintf (&text, "%s%s ", text, file_word) == -1) {
			puts("asprintf err main");
			exit(EXIT_FAILURE);
		}
	}
	if (fclose(fp)) {
		puts("Failed closing file");
		exit(EXIT_FAILURE);
	}

	printf ("%s\n", text);

	char* simvols;
	scanf ("%s", simvols);
	printf("\n");

	if (strpbrk (punctuation_marks, simvols) != NULL){
		printf("Bad simvols : %s\n", simvols);
	}
	else if (find_word (text, simvols) == -1)
			printf ("Dont find this word in yours simvols : %s\n", simvols); 
}

int find_word (char* text, char* word) { 
	if ((text =  strstr (text, word)) == NULL) {
		free (text);
		return -1;
	}

	while(text != NULL) {
		text = find_begin_of_word (text);
		print_word (text);

		text = strstr (strchr (text, ' '), word);
	}

	return 1;
}

char* find_begin_of_word (char* text) {
	while (strchr (punctuation_marks, text[0]) == NULL) {
		--text;
	}
	++text;

	return text;
}

void print_word (char* text) {
	size_t word_size = strpbrk (text, punctuation_marks) - text;

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
