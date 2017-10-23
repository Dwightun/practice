#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

/*
fixit: из название файла неясно, что внутри него. 
можно было бы создать два заголовочных файла. один - Utils.h со split'ом и конвертацией 
времени, второй ExecuteCommand.h, c ф-ей ExecuteWithDelay
*/

void Split(char* string, char* delimiter, char** tokens, int* tokens_Count);
void time_conv(char* string_of_data, int* delay_time);
void use_with_delay(char** commands, int* delay, int number_of_command);
