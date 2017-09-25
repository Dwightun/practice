﻿#pragma warning(disable : 4996)

#include"Header.h"

#define smallN 2
#define N 1000


void Split(char* string, char* delimiter, char** tokens, int* tokens_Count) {
	if (string != NULL && delimiter != NULL && tokens != NULL && tokens_Count != NULL)
	{
		//printf("we are in split\n");
		char* str_out;
		int token_counter = 0;
		char* string_word;
		char* string_copy;
		string_copy = (char*)malloc(sizeof(char)*N);
		string_word = (char*)malloc(sizeof(char)*N);
		string_copy = string;
		strcat(string_copy, delimiter);
		for (int iterator = 0; iterator < (int)strlen(string) + 1; iterator++)
		{
			int x = strlen(string_copy);
			// в целом, конечно, ваш подход с strstr выглядит жестоко ... man про strtok вы точно не смотрели)
			// re: я думал нужно реализовать именно алгоритм поиска лексем, иначе задача получается типа : 3 * x = 3 solve for x
			str_out = strstr(string_copy, delimiter);
			//printf("%x ---- %x\n",str_out,tokens[token_counter]);
			if (str_out != NULL && tokens[token_counter] != NULL)
			{
				//printf("f1\n");
				string_word = str_out;
				//printf("f2\n");
				strncpy(tokens[token_counter], string_copy, strlen(string_copy) - strlen(string_word));
				//printf("f3\n");
				tokens[token_counter][strlen(string_copy) - strlen(string_word)] = '\0';
				//printf("f4\n");
				string_copy = string_word + strlen(delimiter);
				//printf("woop%s\n", tokens[token_counter]);
				if (strlen(tokens[token_counter]) > 0)
					token_counter++;
			}
		}
		*tokens_Count = token_counter;
		//free(string_copy);
		//free(string_word);
	}
}

void func(char* string_of_data, int* delay_time) {
	int start_time;
	char *time_delimiter;
	char **data_array;
	int data_constant = 0;
	time_delimiter = (char*)calloc(smallN, sizeof(char));
	time_delimiter[0] = '/';
	//printf("----%s \n", time_delimiter);
	data_array = (char**)malloc(sizeof(char*) * N);
	if ( string_of_data == NULL || delay_time == NULL)
	{
		printf("NULL POINTER");
		return;
	}
	for (size_t iterator = 0; iterator < N; iterator++)
	{
		data_array[iterator] = (char*)malloc(sizeof(char) * N);
	}
	//printf("wizzz %s\n", string_of_data);
	Split(string_of_data, time_delimiter, data_array, &data_constant);
	//data_array[6][0] = '\0';
	//printf("f1\n");
	//printf("%s \n", data_array[0]);
	//printf("f2\n");
	for (size_t i = 0; i < 6; i++)
	{
		//printf("%d \n", atoi(data_array[i]));
	}
	// тут можно было бы это сделать нормально, но зачем ¯\_(ツ)_/¯
	start_time = atoi(data_array[0]) * 2629743 + atoi(data_array[1]) * 86400 + (atoi(data_array[2]) - 1970) * 31556926 + atoi(data_array[3]) * 3600 + atoi(data_array[4]) * 60 + atoi(data_array[5])- (int)time(NULL);
	//printf("f1");
	*delay_time = start_time;
	for (size_t iterator = 0; iterator < N; iterator++)
	{
		free(data_array[iterator]);
	}
	free(data_array);
	free(time_delimiter);
}

void use_with_delay(char** commands, int* delay, int number_of_command) {
	printf("we are in func = use_with_delay\n");
	for(size_t i = 0; i < (size_t)number_of_command; i++)
	{
		commands[i] = commands[i + 1];
	}
	commands[number_of_command] = '\0';
	for (size_t i = 0; i < number_of_command - 1; i++)
	{
		printf("wabulabudabdab %s\n", commands[i]);
	}
	
//	sleep(*delay);
	execvp(commands[0], commands);
}
