#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
//#include <unistd.h>
//#include <sys/wait.h>

/*
fixit: из название файла неясно, что внутри него. 
можно было бы создать два заголовочных файла. один - Utils.h со split'ом и конвертацией 
времени, второй ExecuteCommand.h, c ф-ей ExecuteWithDelay
*/

void split(char* string, char* delimiter, char** tokens, int* tokens_Count);
void time_conv(char* string_of_data, int* delay_time);
void use_with_delay(char** commands, int* delay, int number_of_command);
int mem_alloc(char *text_of_command_list, char** string_of_commands, char*** words_of_commands, char* string_delimiter, char *word_delimiter, int** delay_time, int** count_of_word_of_string_of_commands, int count_of_strings_of_commands, int size_of_input, int size_of_command_list);
int read_file(FILE* command_list, long* size_of_command_list, int* count_of_strings_of_commands, int* size_of_input, char *text_of_command_list);