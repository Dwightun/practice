#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
//#include <unistd.h>

#define N 1000

void Split(char* string, char* delimiter, char** tokens, int* tokensCount);

int main(){
	char *text_of_comand_list;
	int i = 0;
	char **string_of_commands;
	char **words_of_commands;
	char string_delimiter = '\n';
	char word_delimiter = ' ';
	int count_of_commands = 0;
	int *count_of_word_of_string_of_commands = 0;
	FILE *comand_list = fopen("input.txt", "r");
	if (comand_list == NULL) {
		printf("file not exist");
		exit(1);
	}
	else {
		comand_list = (char*)malloc(sizeof(char*)*N);
		text_of_comand_list = (char*)malloc(sizeof(char*)*N);
		string_of_commands = (char**)malloc(sizeof(char*)*N);
		words_of_commands = (char**)malloc(sizeof(char)*N);
		//malloc 4x
		fscanf(comand_list, &text_of_comand_list);
		Split(text_of_comand_list, &string_delimiter, string_of_commands, &count_of_commands);
		for (int i = 0; i < count_of_commands; i++) {
			Split(&string_of_commands[i], &word_delimiter, words_of_commands, count_of_word_of_string_of_commands);
		}
		execv(words_of_commands[0], &words_of_commands, (char*)NULL);
	}
	FILE *f = fopen("output.txt", "w");
	fprintf(f, "jopa");
	fclose(f);
	fclose(comand_list);
	return 0;
}

void Split(char* string, char* delimiter, char** tokens, int* tokensCount) {
	if (string == NULL || delimiter == NULL || tokens == NULL || tokensCount == NULL)
	{
		errno = "EINVAL";
	}
	else {
		int j = 0;
		char* string_word;
		string_word = (char*)malloc(sizeof(char)*N);
		strcat(string, delimiter);
		for (int i = 0; i < strlen(string); i++)
		{
			if (strstr(string, delimiter) == NULL)
				break;
			else
			{
				string_word = strstr(string, delimiter);
				strncpy(tokens[j], string, strlen(string) - strlen(string_word));
				tokens[j][strlen(string) - strlen(string_word)] = '\0';
				string = string_word + strlen(delimiter);
				if (tokens[j][0] != 0)
					j++;
			}
		}
		*tokensCount = j;
	}
}