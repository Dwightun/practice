#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#define N 1024


void* mine_write(void* fd_1){
	int fd = *((int*)fd_1);
	char *input;
	input=calloc(N, sizeof(char));
	while (1)
	{
		fgets(input,N*sizeof(char),stdin);
		if(strlen(input)<1) sleep(0.1);
		else{
			write(fd,input,(N)*sizeof(char));
		}
		
	}
}

void* mine_read(void* fd_2){
	int fd = *((int*)fd_2);
	int er = 0;
	char *output;
	output = calloc(N, sizeof(char));
	do{
		er = read(fd, output, N);
		printf("ans:%s", output);
	}
	while (er>0);
}

int main(int argc, char **argv){
	char *input;
	char *output;
	char *filename_1 = "fifo_to.fifo";
	char *filename_2 = "fifo_in.fifo";
	if (access(filename_1, F_OK) == -1)
	if (mknod(filename_1, S_IFIFO | 0666, 0) < 0){
		exit(-1);
	}
	if (access(filename_2, F_OK) == -1)
	if (mknod(filename_2, S_IFIFO | 0666, 0) < 0){
		exit(-1);
	}
	int fd_1 = open(((atoi(argv[1]) == 0) ? filename_1 : filename_2), 'r');
	pthread_t th;
	int status = pthread_create(&th, NULL, mine_read, &fd_1);
	int fd_2 = open(((atoi(argv[1]) == 0) ? filename_2 : filename_1), O_WRONLY);
	pthread_t th_1;
	int status_1 = pthread_create(&th_1, NULL, mine_write, &fd_2);
	pthread_join(th, NULL);
	pthread_join(th_1, NULL);
	return 0;	
}
		
