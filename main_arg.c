#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
//#include <cerrno>  
//#include <unistd.h>
extern int errno;

#define N 1000

void Split(char* string, char* delimiter, char** tokens, int* tokensCount);

int main(){
	errno = 0;
	char *text_of_comand_list;
	int er = 0;
	int i = 0;
	char **string_of_commands;
	char **words_of_commands;
	char string_delimiter = '\n';
	char word_delimiter = ' ';
	int count_of_strings_of_commands = 0;
	int *count_of_word_of_string_of_commands = 0;
	FILE *comand_list;
	comand_list = fopen("input.txt", "r+");
	if (comand_list == NULL) {
		printf("file not exist");
		exit(1);
	}
	else {
		text_of_comand_list = (char*)malloc(sizeof(char)*N);
		string_of_commands = (char**)malloc(sizeof(char*)*N);
		words_of_commands = (char**)malloc(sizeof(char*)*N);
		//malloc 4x
		text_of_comand_list[i] = (char*)malloc(sizeof(char)*N);
		er = fread(text_of_comand_list, sizeof(char), N, comand_list);
		text_of_comand_list[er] = '\0';
		printf("%s \n", text_of_comand_list);
		Split(text_of_comand_list, &string_delimiter, string_of_commands, &count_of_strings_of_commands);
		for (i = 0; i < count_of_strings_of_commands; i++) {
			Split(words_of_commands, string_of_commands, words_of_commands,&count_of_word_of_string_of_commands[i]);
		}
		//execv(words_of_commands[0], words_of_commands, (char*)NULL);
		free(text_of_comand_list);
		free(string_of_commands);
		free(words_of_commands);
	}
	FILE *f = fopen("output.txt", "w");
	fprintf(f, "jopa");
	fclose(f);
	fclose(comand_list);
	system("pause");
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
		for (int i = 0; i < strlen(string) + 1; i++)
		{
			if (strstr(string, delimiter) == NULL)
				break;
			else
			{
				string_word = strstr(string, delimiter);
				strncpy(tokens[j], string, strlen(string) - strlen(string_word));
				tokens[j][strlen(string) - strlen(string_word)] = '\0';
				string = string_word + strlen(delimiter);
				if (tokens[j][0] != '\0')
					j++;
			}
		}
		*tokensCount = j;
	}
}