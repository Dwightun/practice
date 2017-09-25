#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>

int main(){
	int height = 0;
	pid_t pid;
	pid_t* pid_array;
	int id = 10000;
	printf("gimme height\n");
	scanf("%d", &height);
	pid_array = (pid_t*)calloc(height, sizeof(pid_t));
	for (size_t i = 0; i < (size_t)height; i++)
	{
		pid = fork();
		if(pid == 0)
		{
			//pid_array[i] = fork();
			id += i;
			printf("i am son = %d\n", id);
			if(pid > 0)
			{
				wait();
			}
		}
		else
		{
			printf("waiting for %d", id);
			wait();
		}
	}
}
