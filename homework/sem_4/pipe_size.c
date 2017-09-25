#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int fd_1[2];
	int fd_2[2];
	int buff[2];
	int input[2];
	buff[0] = 10;
	buff[1] = 15;
	int buffer[1];
	pipe(fd_1);
	write(fd_2[1],buff,2);
	pid_t pid = fork();
	if(pid != 0){
		printf("father start\n");
		pipe(fd_1);
		printf("f1\n");
		sleep(1);
		printf("f2\n");
		write(fd_2[1],buff,2);
		printf("%d  %d\n",buff[0],buff[1]);
		printf("f3\n");
		sleep(10);
		read(fd_2[0],buffer,1);
		printf("f4n");
		printf("%d\n", buffer[0]);
	}
	else{	
		printf("son start\n");
		pipe(fd_2);
		printf("s1\n");
		//sleep(2);
		printf("slept");
		read(fd_1[0],input,2);
		printf("s2\n");
		input[0] += input[1];
		printf("s3\n");
		write(fd_1[1],input,1);
		printf("son end\n");
		exit(0);
	}
	return 0;
}
