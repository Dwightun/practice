#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
//#include <unistd.h>
#define smallN 2
#define N 100

void Split(char* string, char* delimiter, char** tokens, int* tokens_Count);
void func(char* string_of_data, int* daley_time);

int main(){
	char *text_of_comand_list;
	int er = 0;
	int i = 0;
	char **string_of_commands;
	char ***words_of_commands;
	char *string_delimiter;
	char *word_delimiter;
	int count_of_strings_of_commands = 0;
	int **count_of_word_of_string_of_commands;
	int *daley_time;
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
		daley_time = (int*)calloc(N, sizeof(int));
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
			for (size_t i = 0; i < N; i++){
				words_of_commands[iterator][i] = (char*)calloc(N, sizeof(char));
			}
		}
	string_of_commands[0][0] = 'a';
	//printf("%x \n", &count_of_strings_of_commands);
		Split(text_of_comand_list, string_delimiter, string_of_commands, &count_of_strings_of_commands);
		for (size_t j = 0; j < count_of_strings_of_commands; j++ ){
			printf("%s = %d\n", string_of_commands[j], count_of_strings_of_commands);
		}
		words_of_commands[0][0][0] = 'a';
		for (size_t i = 0; i < count_of_strings_of_commands; i++) {
			Split(string_of_commands[i], word_delimiter, words_of_commands[i], count_of_word_of_string_of_commands[i]);
		}
		for (size_t j = 0; j < count_of_strings_of_commands; j++) {
			for (size_t i = 0; i < count_of_word_of_string_of_commands[j][0]; i++) {
				printf("%s   ", words_of_commands[j][i]);
			}
			printf("= %d\n", count_of_word_of_string_of_commands[j][0]);
		}
		//execv(words_of_commands[0], words_of_commands, (char*)NULL);
		//system("pause");
		//func(count_of_word_of_string_of_commands[0][0], daley_time);
		free(text_of_comand_list);
		free(string_of_commands);
		free(words_of_commands);
	}
	FILE *f = fopen("output.txt", "w");
	fprintf(f, "jopa");
	fclose(f);
	fclose(comand_list);
	system("pause");
	return 0;
}

void Split(char* string, char* delimiter, char** tokens, int* tokens_Count) {
	if (string == NULL || delimiter == NULL || tokens == NULL || tokens_Count == NULL) {
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

void func(char* string_of_data, int* daley_time) {
	struct tm start_time;
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
	start_time.tm_mon = atoi(data_array[0]);
	start_time.tm_mday = atoi(data_array[1]);
	start_time.tm_year = atoi(data_array[2]);
	start_time.tm_hour = atoi(data_array[3]);
	start_time.tm_min = atoi(data_array[4]);
	start_time.tm_sec = atoi(data_array[5]);
	*daley_time = (int)(time(&start_time) - time(NULL));
	for (size_t iterator = 0; iterator < N; iterator++)
	{
		free(data_array[iterator]);
	}
}
