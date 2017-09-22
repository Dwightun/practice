#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int fd[2];
	pipe(fd);
	char d[1];
	d[0]=1;
	int i=0;
	while(1){
		write(fd[1],d,1);
		printf("%d\n",i++);
	}
}
