#include <stdio.h>
#include <sys/unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <string.h>

#define NLINE 1000

int main() {
	int fd[2];
	char data[NLINE];
	if (pipe(fd) < 0) {
		printf("Can\'t create pipe\n");
		exit(-1);
	}
	// создали пип
	char pathname_from[NLINE];
	char pathname_to[NLINE];
	printf("gimme source\n");
	fgets(pathname_from, NLINE, stdin);
	printf("gimme dest\n");
	fgets(pathname_to, NLINE, stdin);
	pathname_from[strlen(pathname_from) - 1] = 0;
	pathname_to[strlen(pathname_to) - 1] = 0;
	// прочитали пути
	pid_t result = fork();
	if (result > 0) {
		// писалка
		close(fd[0]);
		int fd_in = open(pathname_from, O_RDONLY);	
		if (fd_in == -1) {
			printf("Can\'t open source\n");
			exit(-1);
		}
		int size = read(fd_in, &data, NLINE);
		if (size < 0) {
			printf("Can\'t read\n");
			exit(-1);
		}
		if (write(fd[1], &size, sizeof(size)) < 0) {
			printf("Can\'t write size\n");
			exit(-1);
		}
		if (write(fd[1], data, size) < 0) {
			printf("Can\'t write data\n");
			exit(-1);
		}
		close(fd[1]);
		close(fd_in);
	}
	else {
		// читалка
		close(fd[1]);
		int in_size;
		if (read(fd[0], &in_size, sizeof(in_size)) < 0) {
			printf("Can\'t read size\n");
			exit(-1);
		}
		if (read(fd[0], data, in_size) < 0 ) {
			printf("Er with reading\n");
			exit(-1);
		}
		int fd_out = open(pathname_to, O_WRONLY | O_CREAT, 0644);
		if (write(fd_out, data, in_size) != in_size) {
			printf("Er with writing\n");
			exit(-1);
		}
		printf("we did it\n");
		close(fd[0]);
		close(fd_out);
	}
	waitpid(result, NULL, 0);
	return 0;
}