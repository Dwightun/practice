#pragma warning(disable : 4996)

#include "Header.h"

#define smallN 2
#define N 100

int main() {
	char *text_of_comand_list;
	int er = 0;
	int i = 0;
	char **string_of_commands;
	char ***words_of_commands;
	char *string_delimiter;
	char *word_delimiter;
	int count_of_strings_of_commands = 0;
	int **count_of_word_of_string_of_commands;
	int **delay_time;
	FILE *comand_list;
	comand_list = fopen("input.txt", "r+");
	if (comand_list == NULL) {
		printf("file not exist");
		exit(1);
	}
	else {
		text_of_comand_list = (char*)calloc(N, sizeof(char));
		string_of_commands = (char**)calloc(N, sizeof(char*));
		words_of_commands = (char***)calloc(N, sizeof(char**));
		string_delimiter = (char*)calloc(smallN, sizeof(char));
		count_of_word_of_string_of_commands = (int**)calloc(N, sizeof(int*));
		word_delimiter = (char*)calloc(smallN, sizeof(char));
		delay_time = (int**)calloc(N, sizeof(int*));
		//malloc 4x
		string_delimiter[0] = '\n';
		word_delimiter[0] = ' ';
		text_of_comand_list = (char*)calloc(N, sizeof(char));
		er = fread(text_of_comand_list, sizeof(char), N, comand_list);
		text_of_comand_list[er] = '\0';
		printf("%s \n", text_of_comand_list);
		for (int iterator = 0; iterator < N; iterator++) {
			count_of_word_of_string_of_commands[iterator] = (int*)calloc(N, sizeof(int));
			string_of_commands[iterator] = (char*)calloc(N, sizeof(char));
			words_of_commands[iterator] = (char**)calloc(N, sizeof(char*));
			delay_time[iterator] = (int*)calloc(N, sizeof(int));
			for (size_t i = 0; i < N; i++) {
				words_of_commands[iterator][i] = (char*)calloc(N, sizeof(char));
			}
		}
		string_of_commands[0][0] = 'a';
		//printf("%x \n", &count_of_strings_of_commands);
		Split(text_of_comand_list, string_delimiter, string_of_commands, &count_of_strings_of_commands);
		for (size_t j = 0; j < count_of_strings_of_commands; j++) {
			printf("%s = %d\n", string_of_commands[j], count_of_strings_of_commands);
		}
		words_of_commands[0][0][0] = 'a';
		for (size_t i = 0; i < count_of_strings_of_commands; i++) {
			Split(string_of_commands[i], word_delimiter, words_of_commands[i], count_of_word_of_string_of_commands[i]);
		}
		for (size_t j = 0; j < count_of_strings_of_commands; j++) {
			for (size_t i = 0; i < count_of_word_of_string_of_commands[j][0]; i++) {
				printf("%s/", words_of_commands[j][i]);
			}
			printf("= %d\n", count_of_word_of_string_of_commands[j][0]);
		}
		execvp(words_of_commands[0][1], words_of_commands[0]);
		printf("%s\n",words_of_commands[0][30]);
		//system("pause");
		for (size_t iterator = 0; iterator < count_of_strings_of_commands; iterator++)
		{
			func(words_of_commands[iterator][0], delay_time[iterator]);
			printf("%d\n", delay_time[iterator][0]);
		}
		//free(text_of_comand_list);
		//free(string_of_commands);
		//free(words_of_commands);
	}
	FILE *f = fopen("output.txt", "w");
	fprintf(f, "jopa");
	fclose(f);
	fclose(comand_list);
	//system("pause");
	return 0;
}
