#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
void Split(char* string, char* delimiter, char*** tokens, int* tokensCount);

int main() {
	char* string;
	char* delimiter;
	char** tokens;
	int tokensCount;
	string = (char*)malloc(sizeof(char)*N);
	delimiter = (char*)malloc(sizeof(char)*N);
	for (int i = 0; i < strlen(string); i++)
	{
		tokens[i] = (char*)malloc(sizeof(char)*N);
	}
	for (int i = 0; i < tokensCount; i++)
	{
		printf("%s", tokens[i]);
	}
	system("pause");
	return 0;
}

void Split(char* string, char* delimiter, char*** tokens, int* tokensCount) {
	int j=0;
	char* string_word;
	string_word = (char*)malloc(sizeof(char)*N);
	for (int i = 0; i < strlen(string); i++)
	{
		if (strstr(string, delimiter) == NULL)
			break;
		else
		{
			string_word = strstr(string, delimiter);
			memcpy(tokens[j], string, strlen(string) - strlen(string_word));
			j++;
			string = string_word+strlen(delimiter);
		}
	}
	tokensCount = j;
}