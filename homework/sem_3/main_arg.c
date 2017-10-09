#include "Header.h"

#define smallN 2 // что значит smallN? нужно либо понятное название, либо коммент
#define N 1000

int main(int argc, char* argv[]) {
	/*
	fixit: переменные не обязательно объялять все в одном месте...
	объявляйте переменную там, где она впервые требуется: куда лучше минимизировать время
	жизни локальных переменных, что был меньше шанс совершить ошибку
	*/
	char *text_of_command_list;
	int size_of_input = 0;
	char **string_of_commands;
	char ***words_of_commands;
	char *string_delimiter;
	char *word_delimiter;
	int count_of_strings_of_commands = 0;
	int **count_of_word_of_string_of_commands;
	int **delay_time;
	size_t iterator;
	size_t i;
	size_t i1;
	size_t i2;
	FILE *command_list = fopen("input.txt", "r+");
	if (command_list != NULL) {
	/*
	fixit: разбейте этот код на отдельные ф-и: считать строки, посплитить, запустить ...
	на этот монолитный код сложно смотреть.
	*/		
		
		string_delimiter = (char*)calloc(smallN, sizeof(char)); //freed
		string_delimiter[0] = '\n';
		word_delimiter = (char*)calloc(smallN, sizeof(char)); //freed
		word_delimiter[0] = ' ';
		fseek(command_list, 0, SEEK_END);
		long size_of_command_list = ftell(command_list);
		fseek(command_list, 0, SEEK_SET);
		while (!feof(command_list)){
			if (fgetc(command_list) == '\n')
				count_of_strings_of_commands++;
		}
		fseek(command_list, 0, SEEK_SET);
		text_of_command_list = (char*)calloc(size_of_command_list, sizeof(char)); //freed
		size_of_input = fread(text_of_command_list, sizeof(char), size_of_command_list, command_list);
		text_of_command_list[size_of_input] = '\0';
		string_of_commands = (char**)calloc(size_of_input, sizeof(char*)); //freed
		words_of_commands = (char***)calloc(N, sizeof(char**)); //unsure about it
		delay_time = (int**)calloc(count_of_strings_of_commands, sizeof(int*)); //freed
		count_of_word_of_string_of_commands = (int**)calloc(count_of_strings_of_commands, sizeof(int*));
		for (iterator = 0; iterator < (size_t)count_of_strings_of_commands; iterator++){
			string_of_commands[iterator] = (char*)calloc(N, sizeof(char)); //freed
			delay_time[iterator] = (int*)calloc(N, sizeof(int)); //freed
			words_of_commands[iterator] = (char**)calloc(N, sizeof(char*)); //freed
			count_of_word_of_string_of_commands[iterator] = (int*)calloc(N, sizeof(int)); //freed
			for (i = 0; i < N; i++){
				words_of_commands[iterator][i] = (char*)calloc(N, sizeof(char)); //freed
			}
		}
		Split(text_of_command_list, string_delimiter, string_of_commands, &count_of_strings_of_commands);
		for (i = 0; i < (size_t)count_of_strings_of_commands; i++) {
			Split(string_of_commands[i], word_delimiter, words_of_commands[i], count_of_word_of_string_of_commands[i]);
		}
		for (iterator = 0; iterator < (size_t)count_of_strings_of_commands; iterator++){
			time_conv(words_of_commands[iterator][0], delay_time[iterator]);
		}
		i = 0;
		/*
		fixit: почему здесь не for, а while?
		*/
		while (count_of_strings_of_commands > i)
		{
			pid_t pid;
			pid = fork();
			if(pid == 0){
				use_with_delay(words_of_commands[i], delay_time[i], count_of_word_of_string_of_commands[i][0]);
				exit(0);
			}
		else{
			// fixit: у вас перед запуском следующей команды родитель дожидается завершения предыдущей?
			// а что если уже пора запустить следующую, а предыдущая очень долго работает?
			wait();
		}
			i++;
		}
		
		/*
		fixit: назовите переменные i1, i2 более осмысленно
		либо, т.к. циклы простые, то можно назвать i,j но объявить переменные рядом с циклом
		*/
		for (i1 = 0; i1 < (size_t)count_of_strings_of_commands; i1++){
			for (i2 = 0; i2 < N; i2++){
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
	return 0;
}
