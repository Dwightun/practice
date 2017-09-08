#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define N 1000
void Split(char* string, char* delimiter, char*** tokens, int* tokensCount);

int main() {
	char* string;
	char* delimiter;
	char** tokens;
	int tokensCount;
	string = (char*)malloc(sizeof(char)*N);
	delimiter = (char*)malloc(sizeof(char)*N);
	scanf("%s %s",string,delimiter);
//	Split(string,delimiter,&tokens,&tokensCount);
	for (int i = 0; i < strlen(string); i++)
	{
		printf("kf\n");
		tokens = (char**)malloc(sizeof(char*)*100);
		printf("i m gay3\n");
	}
	Split(string,delimiter,&tokens,&tokensCount);
	printf("ferum\n");
	for (int i = 0; i < tokensCount; i++)
	{
		printf("%s \n", tokens[i]);
	}
	printf("%d", tokensCount);
	//system("pause");
	return 0;
}

void Split(char* string, char* delimiter, char*** tokens, int* tokensCount) {
	int j=0;
	char* string_word;
	string_word = (char*)malloc(sizeof(char)*N);
	printf("i m gay4\n");
	for (int i = 0; i < strlen(string); i++)
	{
		printf("kick me\n");
		if (strstr(string, delimiter) == NULL)
			break;
		else
		{
			string_word = strstr(string, delimiter);
			printf("ku\n");
			memcpy(tokens[j], string, strlen(string) - strlen(string_word));
			printf("he\n");
			j++;
			string = string_word+strlen(delimiter);
			printf("fuck you asshole\n");
		}
	}
	*tokensCount = j;
	printf("fit\n");
}
