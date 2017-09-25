#pragma warning(disable : 4996)

#include "Header.h"

#define smallN 2
#define N 1000

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
	FILE *command_list;
	command_list = fopen("input.txt", "r+");
	FILE *f = fopen("output.txt", "w");
	if (command_list == NULL) {
		printf("file not exist");
		exit(1);
	}
	else {
		string_delimiter = (char*)calloc(smallN, sizeof(char));
		string_delimiter[0] = '\n';
		word_delimiter = (char*)calloc(smallN, sizeof(char));
		word_delimiter[0] = ' ';
		fseek(command_list, 0, SEEK_END);
		long size_of_command_list = ftell(command_list);
		//printf("%ld \n", size_of_command_list);
		fseek(command_list, 0, SEEK_SET);
		while (!feof(command_list))
		{
			if (fgetc(command_list) == '\n')
				count_of_strings_of_commands++;
		}
		fseek(command_list, 0, SEEK_SET);
		text_of_command_list = (char*)calloc(size_of_command_list, sizeof(char));
		er = fread(text_of_command_list, sizeof(char), size_of_command_list, command_list);
		//text_of_command_list[er] = '\n';
		//text_of_command_list[er + 1] = '\0';
		//printf("%d \n", er);
		text_of_command_list[er] = '\0';
		//printf("%s \n", text_of_command_list);
		string_of_commands = (char**)calloc(N, sizeof(char*));
		words_of_commands = (char***)calloc(N, sizeof(char**));
		delay_time = (int**)calloc(count_of_strings_of_commands, sizeof(int*));
		for (size_t iterator = 0; iterator < (size_t)count_of_strings_of_commands; iterator++)
		{
			string_of_commands[iterator] = (char*)calloc(N, sizeof(char));
			delay_time[iterator] = (int*)calloc(N, sizeof(int));
			words_of_commands[iterator] = (char**)calloc(N, sizeof(char*));
		}
		Split(text_of_command_list, string_delimiter, string_of_commands, &count_of_strings_of_commands);
		/*
		for (size_t i = 0; i < count_of_strings_of_commands; i++)
		{
			printf("i=%d  %s \n",i, string_of_commands[i]);
		}*/
		count_of_word_of_string_of_commands = (int**)calloc(count_of_strings_of_commands, sizeof(int*));

		for (size_t iterator = 0; iterator < (size_t)count_of_strings_of_commands; iterator++)
		{
			count_of_word_of_string_of_commands[iterator] = (int*)calloc(N, sizeof(int));
			for (size_t i = 0; i < N; i++)
			{
				words_of_commands[iterator][i] = (char*)calloc(N, sizeof(char));
			}
		}
		for (size_t i = 0; i < (size_t)count_of_strings_of_commands; i++) {
			Split(string_of_commands[i], word_delimiter, words_of_commands[i], count_of_word_of_string_of_commands[i]);
		}
		
		for (size_t i = 0; i < (size_t)count_of_strings_of_commands; i++)
		{
			for (size_t j = 0; j < (size_t)count_of_word_of_string_of_commands[i][0]; j++)
			{
				printf("%d = %d = %s ", i, j, words_of_commands[i][j]);
			}
			printf("\n");
		}
		//system("pause");
		printf("goose\n");
		for (size_t iterator = 0; iterator < (size_t)count_of_strings_of_commands; iterator++)
		{
			printf("%d | = %s\n", iterator, words_of_commands[iterator][0]);
			func(words_of_commands[iterator][0], delay_time[iterator]);
			printf("..........................................%d\n", delay_time[iterator][0]);
		}
		i = 0;
		printf("megagoose\n");
		printf("count_of_strings_of_commands  = %d\n", count_of_strings_of_commands );
		printf("supermegagoose\n");
		while (count_of_strings_of_commands > i)
		{
			printf("**********  i = %d\n", i);
			pid_t pid;
			pid = fork();
			if(pid == 0)
			{
				printf("powerfulgloriousgipermegagoose\n");
				use_with_delay(words_of_commands[i], delay_time[i], count_of_word_of_string_of_commands[i][0]);
				exit(0);
			}
			else
			{
				wait();
			}
			i++;
		}
		
		/*
		while (count_of_strings_of_commands > i)
		{
			printf("gipersupermegagoose\n");
			printf("======== %s\n",words_of_commands[i][0]);
			printf("gloriousgipersupermegagoose\n");
			printf("delay_time[i]=%d\n", delay_time[i][0]);
			printf("powerfulgloriousgipermegagoose\n");
			use_with_delay(words_of_commands[i], delay_time[i], count_of_word_of_string_of_commands[i][0]);
			printf("pinkpowerfulgloriousgipermegagoose\n");
			i++;
			printf("__\n");
		}
		*/
		printf("ALLAH AKBAR");
		free(text_of_command_list);
		free(string_delimiter);
		free(words_of_commands);
	}

	fclose(f);
	fclose(command_list);
	system("pause");
	return 0;
}
