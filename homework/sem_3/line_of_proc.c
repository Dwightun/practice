#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int height = 0;
	int iterator = 0;
	int *status;
	pid_t pid;
	printf("gimme height\n");
	scanf("%d", &height);
	for(iterator = 0; iterator < height; iterator++) {
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
