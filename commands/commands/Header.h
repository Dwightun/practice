#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
//#include <unistd.h>
//extern int error = 0;

void Split(char* string, char* delimiter, char** tokens, int* tokens_Count);
void time_conv(char* string_of_data, int* delay_time);
void use_with_delay(char** commands, int* delay, int number_of_command);
