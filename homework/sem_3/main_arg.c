#pragma warning(disable : 4996)


#include "Header.h"

#define smallN 2
#define N 1000

int main(int argc, char* argv[]) {
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
	FILE *command_list;
	command_list = fopen(argv[1], "r+");
	FILE *f = fopen("output.txt", "w");
	if (command_list == NULL) {
		printf("file not exist");
		exit(1);
	}
	else {
		string_delimiter = (char*)calloc(smallN, sizeof(char)); //freed
		string_delimiter[0] = '\n';
		word_delimiter = (char*)calloc(smallN, sizeof(char)); //freed
		word_delimiter[0] = ' ';
		fseek(command_list, 0, SEEK_END);
		long size_of_command_list = ftell(command_list);
		fseek(command_list, 0, SEEK_SET);
		while (!feof(command_list))
		{
			if (fgetc(command_list) == '\n')
				count_of_strings_of_commands++;
		}
		fseek(command_list, 0, SEEK_SET);
		text_of_command_list = (char*)calloc(size_of_command_list, sizeof(char)); //freed
		er = fread(text_of_command_list, sizeof(char), size_of_command_list, command_list);
		text_of_command_list[er] = '\0';
		string_of_commands = (char**)calloc(N, sizeof(char*)); //freed
		words_of_commands = (char***)calloc(N, sizeof(char**)); //unsure about it
		delay_time = (int**)calloc(count_of_strings_of_commands, sizeof(int*)); //freed
		count_of_word_of_string_of_commands = (int**)calloc(count_of_strings_of_commands, sizeof(int*));
		for (size_t iterator = 0; iterator < (size_t)count_of_strings_of_commands; iterator++)
		{
			string_of_commands[iterator] = (char*)calloc(N, sizeof(char)); //freed
			delay_time[iterator] = (int*)calloc(N, sizeof(int)); //freed
			words_of_commands[iterator] = (char**)calloc(N, sizeof(char*)); //freed
			count_of_word_of_string_of_commands[iterator] = (int*)calloc(N, sizeof(int)); //freed
			for (size_t i = 0; i < N; i++)
			{
				words_of_commands[iterator][i] = (char*)calloc(N, sizeof(char)); //freed
			}
		}
		Split(text_of_command_list, string_delimiter, string_of_commands, &count_of_strings_of_commands);
		for (size_t i = 0; i < (size_t)count_of_strings_of_commands; i++) {
			Split(string_of_commands[i], word_delimiter, words_of_commands[i], count_of_word_of_string_of_commands[i]);
		}
		for (size_t iterator = 0; iterator < (size_t)count_of_strings_of_commands; iterator++)
		{
			time_conv(words_of_commands[iterator][0], delay_time[iterator]);
		}
		i = 0;
		while (count_of_strings_of_commands > i)
		{
			pid_t pid;
			pid = fork();
			if(pid == 0){
				use_with_delay(words_of_commands[i], delay_time[i], count_of_word_of_string_of_commands[i][0]);
				exit(0);
			}
			else{
				wait();
			}
			i++;
		}
		for (size_t i1 = 0; i1 < (size_t)count_of_strings_of_commands; i1++)
		{
			for (size_t i2 = 0; i2 < N; i2++)
			{
				free(words_of_commands[i1][i2]);
			}
			free(words_of_commands[i1]);
			free(string_of_commands[i1]);
			free(delay_time[i1]);
			free(count_of_word_of_string_of_commands[i1]);
		}
		free(count_of_word_of_string_of_commands);
		free(delay_time);
		free(string_of_commands);
		free(word_delimiter);
		free(text_of_command_list);
		free(string_delimiter);
		free(words_of_commands);
	}

	fclose(f);
	fclose(command_list);
	//system("pause");
	return 0;
}
