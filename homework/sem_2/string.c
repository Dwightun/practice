
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
	string = (char*)malloc(sizeof(char)*N);
	delimiter = (char*)malloc(sizeof(char)*N);
	//scanf("%s %s", string, delimiter);
	fgets(string, N, stdin);
	string[strlen(string) - 1] = 0;
	fgets(delimiter, N, stdin);
	delimiter[strlen(delimiter) - 1] = 0;
	tokens = (char**)malloc(sizeof(char*)*N);
	for (int iterator = 0; iterator < (int)strlen(string); iterator++)
	{
		tokens[iterator] = (char*)malloc(sizeof(char)*strlen(string));
	}
	Split(string, delimiter, tokens, &tokens_Count);
	for (int iterator= 0; iterator < tokens_Count; iterator++)
	{
		printf("%d = %s\n", iterator, tokens[iterator]);
		free(tokens[iterator]);
	}
	printf("tokens_Count = %d \n", tokens_Count);
	free(string);
	free(delimiter);
	return 0;
}

void Split(char* string, char* delimiter, char** tokens, int* tokens_Count) {
	if (string == NULL || delimiter == NULL || tokens == NULL || tokens_Count == NULL)
	{
		return;
	}
	else {
		char* str_out;
		int token_counter = 0;
		char* string_word;
		string_word = (char*)malloc(sizeof(char)*N);
		strcat(string, delimiter);
		for (int iterator = 0; iterator < (int)strlen(string); iterator++)
		{
			str_out = strstr(string, delimiter);
			if (str_out == NULL)
				break;
			else
			{
				string_word = str_out;
				strncpy(tokens[token_counter], string, strlen(string) - strlen(string_word));
				tokens[token_counter][strlen(string) - strlen(string_word)] = '\0';
				string = string_word + strlen(delimiter);
				if (strlen(tokens[token_counter]) > 0)
					token_counter++;
			}
		}
		*tokens_Count = token_counter;
	}
}