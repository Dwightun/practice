
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <cerrno>  

#define N 1000

void Split(char* string, char* delimiter, char** tokens, int* tokensCount);

int main() {
	errno = 0;
	char* string;
	char* delimiter;
	char** tokens;
	int tokensCount = 0;
	int j = 0;
	char c;
	string = (char*)malloc(sizeof(char)*N);
	delimiter = (char*)malloc(sizeof(char)*N);
	tokens = (char**)malloc(sizeof(char*)*100);
	while ((c = getchar()) != '\n'){
		string[j] = c;
		j++;
	}
	string[j++] = '\0';
	j = 0;
	while ((c = getchar()) != '\n') {
		delimiter[j] = c;
		j++;
	}
	delimiter[j++] = '\0';
	for (int i = 0; i < strlen(string); i++)
	{
		tokens[i] = (char*)malloc(sizeof(char)*strlen(string));
	}
	//string = NULL;
	Split(string,delimiter,tokens,&tokensCount);
	for (int i = 0; i < tokensCount; i++)
	{
		printf("%d = %s\n", i, tokens[i]);
		free(tokens[i]);
	}
	if (errno == 0) {
		printf("%d \n", tokensCount);
	}
	printf("%s \n\n", errno);
	free(string);
	//free(*tokens);
	free(delimiter);
	system("pause");
	return 0;
}

void Split(char* string, char* delimiter, char** tokens, int* tokensCount) {
	if (string==NULL || delimiter==NULL || tokens==NULL || tokensCount==NULL)
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
