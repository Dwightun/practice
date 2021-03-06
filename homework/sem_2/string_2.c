﻿
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define N 1000

void Split(char* string, char* delimiter, char** tokens, int* tokens_Count);

int main() {
	char* string;
	char* delimiter;
	char** tokens;
	int tokens_Count = 0;
	// fixit: пробелы вокруг * -> sizeof(char) * N ... и везде ниже по коду
	string = (char*)malloc(sizeof(char)*N);
	delimiter = (char*)malloc(sizeof(char)*N);
	//scanf("%s %s", string, delimiter);
	
	// у вас следующие две строки повторяются дважды ... вы видимо символ перевода строки удаляете так
	// по-хорошему, любого дублирования кода надо избегать и сделать отдельную ф-ю для считавания
	fgets(string, N, stdin);
	string[strlen(string) - 1] = 0;
	fgets(delimiter, N, stdin);
	delimiter[strlen(delimiter) - 1] = 0;
	tokens = (char**)malloc(sizeof(char*)*N);
	
	// памяти, конечно, прям от души выделили :) ну, дело ваше ...
	for (int iterator = 0; iterator < (int)strlen(string); iterator++)
	{
		tokens[iterator] = (char*)malloc(sizeof(char)*strlen(string));
	}
	
	// fixit: пишут обычно либо tokensCount, либо tokens_count ... используйте 1й вариант, например 
	// это касается и переменных из ф-и Split
	Split(string, delimiter, tokens, &tokens_Count);
	for (int iterator= 0; iterator < (int)tokens_Count; iterator++)
	{
		printf("%d = %s\n", iterator, tokens[iterator]);
	}
	for (int iterator= 0; iterator < (int)strlen(string); iterator++)
	{
		free(tokens[iterator]);
	}
	printf("tokens_Count = %d \n", tokens_Count);
	free(tokens);
	free(string);
	free(delimiter);
	return 0;
}

void Split(char* string, char* delimiter, char** tokens, int* tokens_Count) {
	if (string != NULL && delimiter != NULL && tokens != NULL && tokens_Count != NULL)
	{
		char* str_out;
		int token_counter = 0;
		char* string_word;
		char* string_copy;
		string_copy = (char*)malloc(sizeof(char)*N);
		string_word = (char*)malloc(sizeof(char)*N);
		string_copy = string;
		strcat(string_copy, delimiter);
		for (int iterator = 0; iterator < (int)strlen(string_copy); iterator++)
		{
			// в целом, конечно, ваш подход с strstr выглядит жестоко ... man про strtok вы точно не смотрели)
			// re: я думал нужно реализовать именно алгоритм поиска лексем, иначе задача получается типа : 3 * x = 3 solve for x
			str_out = strstr(string_copy, delimiter);
			if (str_out != NULL && tokens[token_counter] != NULL)
				string_word = str_out;
			strncpy(tokens[token_counter], string_copy, strlen(string_copy) - strlen(string_word));
			tokens[token_counter][strlen(string_copy) - strlen(string_word)] = '\0';
			string_copy = string_word + strlen(delimiter);
			if (strlen(tokens[token_counter]) > 0)
				token_counter++;
		}
		*tokens_Count = token_counter;
		//free(string_copy);
		//free(string_word);
	}
}
