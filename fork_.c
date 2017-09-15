#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
	/*int a = 0;
	pid_t pid = 0;
	pid = fork();
	if (pid == -1){
		exit(1);
	}else if (pid == 0){
		a++;
		printf("goose1 \n");
	}else{
		a++;
		printf("goose2 \n");
	}
	a++;
	printf("%d %d %d \n", getpid(), getppid(), a);
	//printf("goose"); */
	/*printf("1");
	fork();
	printf("2");*/
	int N = 3;
	int x = 0;
	pid_t y = 0;
	for (int i = 0; i < N; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			sleep(1+i);
			printf("%d\n", i);
			exit(0);
		}
	y = wait(&x);
	}
	/*pid_t pid = fork();
	int N = 0;
	while(N < 5){
		if (pid != 0){
			fork();
			printf("%d   \n", getppid());
		}
		N++;
	}*/
	return 0;
} 
	
