#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define N 1000

void Split(char* string, char* delimiter, char** tokens, int* tokensCount);

int main() {
	char* string;
	char* delimiter;
	char** tokens;
	int tokensCount;
	string = (char*)malloc(sizeof(char)*N);
	delimiter = (char*)malloc(sizeof(char)*N);
	scanf("%s %s",string,delimiter);
	tokens = (char**)malloc(sizeof(char*)*100);
	for (int i = 0; i < strlen(string); i++)
	{
		tokens[i] = (char*)malloc(sizeof(char)*strlen(string));
	}
	Split(string,delimiter,tokens,&tokensCount);
	for (int i = 0; i < tokensCount; i++)
	{
		printf("%s \n", tokens[i]);
		free(tokens[i]);
	}
	printf("%d \n", tokensCount);
	system("pause");
	free(string);
	free(*tokens);
	free(delimiter);
	return 0;
}

void Split(char* string, char* delimiter, char** tokens, int* tokensCount) {
	int j=0;

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
			string = string_word+strlen(delimiter);
			j++;
		}
	}
	*tokensCount = j;
}
