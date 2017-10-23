#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

/*
fixit: т.к. на семинаре не все справились с упражнением, то он перешло в разряд домашних.
раз так, то нужно
1) избавиться от дублирования кода
2) магических констант ... 1000
3) убрать отладочный код
*/

void* mine_write(void* fd_1){
	int fd = *((int*)fd_1);
	char *input;
	input=calloc(1000, sizeof(char));
	while (1)
	{
		fgets(input,1000*sizeof(char),stdin);
		//printf("You wrote: %s\n", input);
		if(strlen(input)<1) sleep(0.1);
		else{
			printf("Writing to pipe...\n");
			//write(fd_1, strlen(input), 4);
			write(fd,input,(1000)*sizeof(char));
			printf("Written.\n");
			//fflush(fd_1);
		}
		
	}
}

void* mine_read(void* fd_2){
	int fd = *((int*)fd_2);
	int er=0;
	char *output;
	output=calloc(1000, sizeof(char));
	do
	{
		printf("in read\n");
		//read(fd_2, &ssize, sizeof(int));
		//printf("%d\n", ssize);
		er=read(fd, output, 1000);
		printf("%d er \n",er);
		printf("re_1:%s", output);
	}
	while (er>0);
}

int main(int argc, char **argv){
	char *input;
	char *output;
	char *filename_1 = "fifo_to.fifo";
	char *filename_2 = "fifo_in.fifo";
	int ssize=1;
	if(access(filename_1, F_OK)==-1)
	if (mknod(filename_1, S_IFIFO | 0666, 0) < 0)
	{
		exit(-1);
	}
	if(access(filename_2, F_OK)==-1)
	if (mknod(filename_2, S_IFIFO | 0666, 0) < 0)
	{
		exit(-1);
	}
	printf("arg=%d\n", atoi(argv[1]));
	
	if (atoi(argv[1]) == 0)
	{
		//printf("asd\n")
		int fd_1;
		fd_1= open(filename_1, O_WRONLY);
		printf("fd== %d\n", fd_1);
		pthread_t th;
		printf("th 1 s\n");
		int status = pthread_create(&th, NULL, mine_write, &fd_1);
		printf("th 1 d\n");
		int fd_2 = open(filename_2, O_RDONLY);
		pthread_t th_1;
		printf("th 2 s\n");
		int status_1 = pthread_create(&th_1, NULL, mine_read, &fd_2);
		printf("th 2 d\n");
		pthread_join(th, NULL);
		pthread_join(th_1, NULL);
	}
	if (atoi(argv[1]) == 1)
	{
		//printf("asd\n")
		int fd_1;
		int fd_2 = open(filename_1, O_RDONLY);
		fd_1= open(filename_2, O_WRONLY);
		pthread_t th;
		int status = pthread_create(&th, NULL, mine_write, &fd_1);
		pthread_t th_1;
		int status_1 = pthread_create(&th_1, NULL, mine_read, &fd_2);
		pthread_join(th, NULL);
		pthread_join(th_1, NULL);
	}
		return 0;	
}
		
