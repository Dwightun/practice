#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int height = 0;
	int proccess_index = 0;
	int *status;
	pid_t pid;
	printf("gimme height\n");
	scanf("%d", &height);
	for(proccess_index = 0; proccess_index < height; proccess_index++) {
		pid = fork();
		if(pid == 0) {
			printf("id of child process = %d\n", getpid());
			printf("id of parent process = %d\n", getppid());
		} else {
			wait(status);
			printf("status = %d\n", *status);
			exit(0);
		}
	}
	return 0;
}
