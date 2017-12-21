#include"TimeAndSplit.h"

#define smallN 2
#define N 1000
#define TIME_SIZE_CONSTANT 19
#define TIME_COUNT_CONSTANT 6
#define TIME_UNIT_SIZE_CONSTANT 10


void split(char* string, char* delimiter, char** tokens, int* tokens_count) {
	if (string != NULL && delimiter != NULL && tokens != NULL && tokens_count != NULL){
		char* str_out;
		int token_counter = 0;
		char* string_word;
		char* string_copy;
		string_copy = string;
		strcat(string_copy, delimiter);
		for (int iterator = 0; iterator < (int)strlen(string) + 1; iterator++){
			int x = strlen(string_copy);
			str_out = strstr(string_copy, delimiter);
			if (str_out != NULL && tokens[token_counter] != NULL){
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

void time_conv(char* string_of_data, int* delay_time) {
	char *time_delimiter;
	char **data_array;
	int data_constant = 0;
	time_delimiter = (char*)calloc(smallN, sizeof(char));
	time_delimiter[0] = '/';
	data_array = (char**)calloc(TIME_COUNT_CONSTANT, sizeof(char*));  
	if ( string_of_data == NULL || delay_time == NULL){
		printf("NULL POINTER");
		return;
	}
	for (size_t i = 0; i < TIME_COUNT_CONSTANT; i++){
		data_array[i] = (char*)calloc(TIME_UNIT_SIZE_CONSTANT, sizeof(char));  
	}
	split(string_of_data, time_delimiter, data_array, &data_constant);
	*delay_time = atoi(data_array[0]) * 2629743 + atoi(data_array[1]) * 86400 + (atoi(data_array[2]) - 1970) * 31556926 + atoi(data_array[3]) * 3600 + atoi(data_array[4]) * 60 + atoi(data_array[5])- (int)time(NULL);
	for (size_t iterator = 0; iterator < TIME_COUNT_CONSTANT; iterator++){
		free(data_array[iterator]);
	}
	free(data_array);
	free(time_delimiter);
}

void use_with_delay(char** commands, int* delay, int number_of_command) {
	printf("asdasd\n");
	sleep(*delay);
	execvp(commands[0], commands + 1);
}

int mem_alloc(char* text_of_command_list, char** string_of_commands, char*** words_of_commands, char* string_delimiter, char *word_delimiter, int** delay_time, int** count_of_word_of_string_of_commands, int* count_of_strings_of_commands, int size_of_input, int size_of_command_list) {

	text_of_command_list = (char*)calloc(size_of_command_list, sizeof(char));  
	string_of_commands = (char**)calloc(size_of_input, sizeof(char*));  
	words_of_commands = (char***)calloc(N, sizeof(char**)); //unsure about it
	delay_time = (int**)calloc(count_of_strings_of_commands, sizeof(int*));  
	count_of_word_of_string_of_commands = (int**)calloc(count_of_strings_of_commands, sizeof(int*));
	for (size_t iterator = 0; iterator < (size_t)count_of_strings_of_commands; iterator++) {
		string_of_commands[iterator] = (char*)calloc(N, sizeof(char));  
		delay_time[iterator] = (int*)calloc(N, sizeof(int));  
		words_of_commands[iterator] = (char**)calloc(N, sizeof(char*));  
		count_of_word_of_string_of_commands[iterator] = (int*)calloc(N, sizeof(int));  
		for (size_t i = 0; i < N; i++) {
			words_of_commands[iterator][i] = (char*)calloc(N, sizeof(char));  
		}
	}
	string_delimiter = (char*)calloc(smallN, sizeof(char));  
	string_delimiter[0] = '\n';
	word_delimiter = (char*)calloc(smallN, sizeof(char));  
	word_delimiter[0] = ' ';
	if (text_of_command_list == NULL || string_of_commands == NULL || words_of_commands == NULL || delay_time == NULL || count_of_word_of_string_of_commands == NULL || string_delimiter == NULL || word_delimiter == NULL) return 0;
	return 1;
}

int read_file(FILE* command_list, long* size_of_command_list, int* count_of_strings_of_commands, int* size_of_input, char *text_of_command_list) {
	fseek(command_list, 0, SEEK_END);
	*size_of_command_list = ftell(command_list);
	fseek(command_list, 0, SEEK_SET);
	while (!feof(command_list)) {
		if (fgetc(command_list) == '\n')
			(*count_of_strings_of_commands)++;
	}
	fseek(command_list, 0, SEEK_SET);
	*size_of_input = fread(text_of_command_list, sizeof(char), size_of_command_list, command_list);
	text_of_command_list[*size_of_input] = '\0';
	if (size_of_command_list == NULL)
	{
		return 0;
	}
	return 1;
}