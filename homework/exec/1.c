#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#define N 8192
#define smallN 2
#define TIME_SIZE_CONSTANT 19
#define TIME_COUNT_CONSTANT 6
#define TIME_UNIT_SIZE_CONSTANT 10

typedef struct {
	char *text;
	char **strings;
	char ***words;
	char string_delimiter[2];
	char word_delimiter[2];
	int text_size;
	int text_h;
	int stirngs_count;
	int **words_in_strings_count;
	int *delay_time;
}commands;

void mem_free(commands *list);
void time_conv(char* string_of_data, int* delay_time);
void iter_split(commands *list);
void mem_alloc(commands *list);
int read_file(FILE* command_list, commands *list);
void split(char* string, char* delimiter, char** tokens, int* tokens_count);

int main() {
	FILE *command_list = fopen("./input.txt", "r+");
	if (command_list == NULL) {
		printf("wrong file\n");
		exit(1);
	}
	commands list;
	list.string_delimiter[0] = '\n';
	list.string_delimiter[1] = '\0';
	list.word_delimiter[0] = ' ';
	list.word_delimiter[1] = '\0';
	list.stirngs_count = 0;
	if (read_file(command_list, &list) == 0) {
		printf("empty file\n");
		exit(2);
	}
	mem_alloc(&list);
	// тут конечно можно написать проверку успешности выделения памяти, но if от ~6 сравнений мне не нравится
	iter_split(&list);
	for (int i = 0; i < ((int)list.stirngs_count); i++) {
		time_conv(list.words[i][0], &list.delay_time[i]);
	}
	int pids[list.stirngs_count];
	for (int i = 0; i < (int)list.stirngs_count; i++) {
		pid_t pids[i];
		sleep(1); //sest
		pids[i] = fork();
		if (pids[i] == 0) {
			printf("sleep\n"); //test
			list.delay_time[i] = 1; //test
			sleep(list.delay_time[i]);
			printf("i = %d zero word = %s %s %s\n", i, list.words[i][0], list.words[i][1], list.words[i][2]); //test
			int j = 0;
			while (strlen(list.words[i][j]) != 0) {
				j++;
			}
			list.words[i][j] = NULL;
			printf("goose == %s %s\n", list.words[i][2], list.words[i][3]); //test
			execvp(list.words[i][1], list.words[i] + 1); // здесь не понятно как подаются аргументы
			exit(0);
		}
	}
	sleep(1); //test
	for (int i = 0; i < list.stirngs_count; i++) {
		waitpid(pids[i], NULL, 0);
	}
	sleep(2); //test
	fclose(command_list);
	mem_free(&list);
	return 0;
}

int read_file(FILE* command_list, commands *list) {
	list->text = (char*)calloc(N, sizeof(char));
	fseek(command_list, 0, SEEK_END);
	int size = ftell(command_list);
	fseek(command_list, 0, SEEK_SET);
	char c;
	int k = 0;
	while (!feof(command_list)) {
		if ((c = fgetc(command_list)) == '\n') {
			k++;
		}
	}
	list->stirngs_count = k;
	fseek(command_list, 0, SEEK_SET);
	list->text_size = fread(list->text, sizeof(char), size, command_list);
	list->text[list->text_size] = '\0';
	return size;
}

void mem_alloc(commands *list) {
	list->strings = (char**)calloc(list->text_size, sizeof(char*));
	list->words = (char***)calloc(list->text_size, sizeof(char**));
	list->delay_time = (int*)calloc(list->stirngs_count, sizeof(int*));
	list->words_in_strings_count = (int**)calloc(list->stirngs_count, sizeof(int*));
	for (int i = 0; i < (int)list->stirngs_count; i++) {
		list->strings[i] = (char*)calloc(N / 8, sizeof(char));
		list->words[i] = (char**)calloc(N / 8, sizeof(char*));
		list->words_in_strings_count[i] = (int*)calloc(N / 8, sizeof(int));
		for (int j = 0; j < N / 8; j++) {
			list->words[i][j] = (char*)calloc(N / 8, sizeof(char));
		}
	}
}

void iter_split(commands *list) {
	int useless;
	split(list->text, list->string_delimiter, list->strings, &useless);
	for (int i = 0; i < (int)list->stirngs_count; i++) {
		split(list->strings[i], list->word_delimiter, list->words[i], &list->words_in_strings_count[i][0]);
	}
}

void time_conv(char* string_of_data, int* delay_time) {
	char time_delimiter[2];
	char **data_array;
	int data_constant = 0;
	time_delimiter[0] = '/';
	time_delimiter[1] = '\0';
	data_array = (char**)calloc(TIME_COUNT_CONSTANT, sizeof(char*));
	if (string_of_data == NULL || delay_time == NULL) {
		printf("NULL POINTER\n");
		return;
	}
	for (int i = 0; i < TIME_COUNT_CONSTANT; i++) {
		data_array[i] = (char*)calloc(TIME_UNIT_SIZE_CONSTANT, sizeof(char));
	}
	split(string_of_data, time_delimiter, data_array, &data_constant);
	*delay_time = atoi(data_array[0]) * 2629743 + atoi(data_array[1]) * 86400 + (atoi(data_array[2]) - 1970) * 31556926 + atoi(data_array[3]) * 3600 + atoi(data_array[4]) * 60 + atoi(data_array[5]) - (int)time(NULL);
	for (int iterator = 0; iterator < TIME_COUNT_CONSTANT; iterator++) {
		free(data_array[iterator]);
	}
	free(data_array);
}

void mem_free(commands *list) {
	free(list->text);
	free(list->delay_time);
	for (int i = 0; i < list->stirngs_count; i++) {
		for (int j = 0; j < N / 8; j++) {
			free(list->words[i][j]);
		}
		free(list->strings[i]);
		free(list->words[i]);
		free(list->words_in_strings_count[i]);
	}
	free(list->strings);
	free(list->words);
	free(list->words_in_strings_count);
}

void split(char* string, char* delimiter, char** tokens, int* tokens_count) {
	if (string != NULL && delimiter != NULL && tokens != NULL && tokens_count != NULL) {
		char* str_out;
		int token_counter = 0;
		char* string_word;
		char* string_copy;
		string_copy = string;
		strcat(string_copy, delimiter);
		for (int iterator = 0; iterator < (int)strlen(string) + 1; iterator++) {
			str_out = strstr(string_copy, delimiter);
			if (str_out != NULL && tokens[token_counter] != NULL) {
				string_word = str_out;
				strncpy(tokens[token_counter], string_copy, strlen(string_copy) - strlen(string_word));
				tokens[token_counter][strlen(string_copy) - strlen(string_word)] = '\0';
				string_copy = string_word + strlen(delimiter);
				if (strlen(tokens[token_counter]) > 0)
					token_counter++;
			}
		}
		*tokens_count = token_counter;
	}
}