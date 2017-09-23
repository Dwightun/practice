#pragma warning(disable : 4996)

#include "Header.h"

#define smallN 2
#define N 100

int main() {
	char *text_of_command_list;
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
	FILE *f = fopen("output.txt", "w");
	printf("test");
	if (comand_list == NULL) {
		printf("file not exist");
		exit(1);
	}

	else {
		text_of_command_list = (char*)calloc(N, sizeof(char));
		string_of_commands = (char**)calloc(N, sizeof(char*));
		words_of_commands = (char***)calloc(N, sizeof(char**));
		string_delimiter = (char*)calloc(smallN, sizeof(char));
		count_of_word_of_string_of_commands = (int**)calloc(N, sizeof(int*));
		word_delimiter = (char*)calloc(smallN, sizeof(char));
		delay_time = (int**)calloc(N, sizeof(int*));
		//malloc 4x
		string_delimiter[0] = '\n';
		word_delimiter[0] = ' ';
		text_of_command_list = (char*)calloc(N, sizeof(char));
		er = fread(text_of_command_list, sizeof(char), N, comand_list);
		text_of_command_list[er] = '\0';
		for (int iterator = 0; iterator < N; iterator++) {
			count_of_word_of_string_of_commands[iterator] = (int*)calloc(N, sizeof(int));
			string_of_commands[iterator] = (char*)calloc(N, sizeof(char));
			words_of_commands[iterator] = (char**)calloc(N, sizeof(char*));
			delay_time[iterator] = (int*)calloc(N, sizeof(int));
			for (size_t i = 0; i < N; i++) {
				words_of_commands[iterator][i] = (char*)calloc(N, sizeof(char));
			}
		}
		Split(text_of_command_list, string_delimiter, string_of_commands, &count_of_strings_of_commands);
		for (size_t i = 0; i < (size_t)count_of_strings_of_commands; i++) {
			Split(string_of_commands[i], word_delimiter, words_of_commands[i], count_of_word_of_string_of_commands[i]);
		}
	
		for (size_t iterator = 0;  iterator < (size_t)count_of_strings_of_commands;  iterator++)
		{
			//execvp(words_of_commands[iterator][1], words_of_commands[iterator]);
		}
		printf("%s\n",words_of_commands[0][30]);
		//system("pause");
		for (size_t iterator = 0; iterator < (size_t)count_of_strings_of_commands; iterator++)
		{
			func(words_of_commands[iterator][0], delay_time[iterator]);
			printf("%d\n", delay_time[iterator][0]);
		}
		use_with_delay(words_of_commands[0], delay_time[0], count_of_word_of_string_of_commands[0][0]);
	}

	fclose(f);
	fclose(comand_list);
	system("pause");
	return 0;
}
