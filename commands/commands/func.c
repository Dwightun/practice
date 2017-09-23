#pragma warning(disable : 4996)
#pragma warning(disable : 2019)

#include"Header.h"

#define smallN 2
#define N 100


void Split(char* string, char* delimiter, char** tokens, int* tokens_Count) {
	if (string == NULL || delimiter == NULL || tokens == NULL || tokens_Count == NULL)
	{
		return;
	}
	else {
		char* str_out;
		int token_counter = 0;
		char* string_word;
		char* string_copy;
		string_copy = (char*)malloc(sizeof(char)*N);
		string_word = (char*)malloc(sizeof(char)*N);
		string_copy = string;
		strcat(string_copy, delimiter);
		for (int iterator = 0; iterator < (int)strlen(string_copy); iterator++) {
			str_out = strstr(string_copy, delimiter);
			if (str_out == NULL) {
				break;
			}
			else {
				string_word = str_out;
				int gap = strlen(string_copy) - strlen(string_word);
				strncpy(tokens[token_counter], string_copy, gap);
				tokens[token_counter][strlen(string_copy) - strlen(string_word)] = '\0';
				string_copy = string_word + strlen(delimiter);
				if (strlen(tokens[token_counter]) > 0)
					token_counter++;
			}
		}
		*tokens_Count = token_counter;
	}
}

void func(char* string_of_data, int* delay_time) {
	int start_time;
	char *time_delimiter;
	char **data_array;
	int data_constant = 0;
	time_delimiter = (char*)calloc(smallN, sizeof(char));
	time_delimiter[0] = '/';
	data_array = (char**)malloc(sizeof(char*) * N);
	for (size_t iterator = 0; iterator < N; iterator++)
	{
		data_array[iterator] = (char*)malloc(sizeof(char) * N);
	}
	Split(string_of_data, time_delimiter, data_array, &data_constant);
	start_time = atoi(data_array[0]) * 2629743 + atoi(data_array[1]) * 86400 + (atoi(data_array[2]) - 1970) * 31556926 + atoi(data_array[3]) * 3600 + atoi(data_array[4]) * 60 + atoi(data_array[5])- time(NULL);
	*delay_time = start_time;
	for (size_t iterator = 0; iterator < N; iterator++)
	{
		free(data_array[iterator]);
	}
}

void use_with_delay(char** commands, int* delay, int number_of_command) {
	int i = 0;
	func(commands[number_of_command], delay);
	for(int i = 0; i < number_of_command; i++)
	{
		commands[i] = commands[i + 1];
	}
	sleep(*delay);
	execvp(commands[0], commands);
}