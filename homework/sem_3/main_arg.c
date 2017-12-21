#include "TimeAndSplit.h"

#define smallN 2 // что значит smallN? нужно либо понятное название, либо коммент
#define N 1000

int main(int argc, char* argv[]) {
	char *text_of_command_list;
	int size_of_input = 0;
	char **string_of_commands;
	char ***words_of_commands;
	char *string_delimiter;
	char *word_delimiter;
	int count_of_strings_of_commands = 0;
	int **count_of_word_of_string_of_commands;
	int **delay_time;
	long size_of_command_list;
	size_t iterator;
	size_t i;
	size_t i1;
	size_t i2;
	FILE *command_list = fopen("input.txt", "r+");
	goto da;
	if (command_list != NULL) {
	da:;
		string_delimiter = (char*)calloc(smallN, sizeof(char));
		string_delimiter[0] = '\n';
		word_delimiter = (char*)calloc(smallN, sizeof(char));
		word_delimiter[0] = ' ';
		read_file(command_list, &size_of_command_list, &count_of_strings_of_commands, &size_of_input, text_of_command_list);
		mem_alloc(text_of_command_list, string_of_commands, words_of_commands, string_delimiter, word_delimiter, delay_time, count_of_word_of_string_of_commands, count_of_strings_of_commands, size_of_input, size_of_command_list);
		split(text_of_command_list, string_delimiter, string_of_commands, &count_of_strings_of_commands);
		for (i = 0; i < (size_t)count_of_strings_of_commands; i++) {
			split(string_of_commands[i], word_delimiter, words_of_commands[i], count_of_word_of_string_of_commands[i]);
		}
		for (iterator = 0; iterator < (size_t)count_of_strings_of_commands; iterator++) {
			time_conv(words_of_commands[iterator][0], delay_time[iterator]);
		}
		i = 0;
		while (count_of_strings_of_commands > i){
			pid_t pid;
			pid = fork();
			if (pid == 0) {
				use_with_delay(words_of_commands[i], delay_time[i], count_of_word_of_string_of_commands[i][0]);
				exit(0);
			}
			else {
				wait();
			}
			i++;
		}
		for (i1 = 0; i1 < (size_t)count_of_strings_of_commands; i1++) {
			for (i2 = 0; i2 < N; i2++) {
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
	else {
		printf("file not exist");
		exit(1);
	}
	fclose(command_list);
	system("pause");
	return 0;
}