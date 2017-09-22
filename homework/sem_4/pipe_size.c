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
	buff[0] = 10;
	buff[1] = 15;
	int buffer[2];
	pid_t pid = fork();
	if(getppid()) {
		pipe(fd_1);
		write(fd_1[1],buff,2);
	}
	if(getpid()) {
		int *result;
		pipe(fd_2);
		read(fd_1[0],buffer,2);
		*result = buffer[0]*buffer[1];
		write(fd_2[1],result,1);
	}
	if (getppid()){
		read(fd_2[0],buff,1);
	}
	printf("%d\n", buff[0]);
	return 0;
}
