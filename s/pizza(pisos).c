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

#define SIZE 5

void myop(int id, int val) { //функция оператор семафора
	struct sembuf sb;
	sb.sem_flg = 0;
	sb.sem_num = 0;
	sb.sem_op = val;
	semop(id, &sb, 1);
}

void func(int i, int semid_1, int semid_2, int *sh) { // рабочая функция 
	for (int j = 0; j < SIZE; j++) {
		myop(semid_1, -1);
		if (*sh == i) {
			putc("pisos"[i - 1], stdout);
			fflush(stdout);
			myop(semid_2, SIZE);
		}
		else {
			myop(semid_2, -1);
		}
	}

}



int main() {
	int desk = ftok("jojo", 0);
	int semid_1 = semget(desk, 1, S_IRUSR | S_IWUSR | IPC_CREAT);
	semctl(semid_1, 0, SETVAL, 0);
	desk = ftok("jojo", 1);
	int semid_2 = semget(desk, 1, S_IRUSR | S_IWUSR | IPC_CREAT);
	semctl(semid_2, 0, SETVAL, 0);
	// создано два семафора
	desk = shmget(desk, sizeof(int) * 1, 0666 | IPC_CREAT);
	int* sh = shmat(desk, NULL, 0);
	// создано шеред мем для передачи номера буквы
	pid_t pid;
	int length;
	scanf("%d", &length);
	for (int j = 0; j < length; j++)
	{
		for (int i = 1; i <= SIZE; i++) { // цикл для печати
			pid = fork();
			if (pid == 0) {
				func(i, semid_1, semid_2, sh);
				return 0;
			}
		}
		for (int i = 1; i <= SIZE; i++) { // цикл для регуляции порядка
			*sh = i;
			myop(semid_1, SIZE);
			myop(semid_2, -1);
			printf("  #%d#\n", i); // это костыль
		}
		waitpid(pid, NULL, 0);
		printf("\n");
	}
	printf("\nЗАПУСКАЕМ\n░ГУСЯ░▄▀▀▀▄░РАБОТЯГИ░░\n▄███▀░◐░░░▌░░░░░░░\n░░░░▌░░░░░▐░░░░░░░\n░░░░▐░░░░░▐░░░░░░░\n░░░░▌░░░░░▐▄▄░░░░░\n░░░░▌░░░░▄▀▒▒▀▀▀▀▄\n░░░▐░░░░▐▒▒▒▒▒▒▒▒▀▀▄\n░░░▐░░░░▐▄▒▒▒▒▒▒▒▒▒▒▀▄\n░░░░▀▄░░░░▀▄▒▒▒▒▒▒▒▒▒▒▀▄\n░░░░░░▀▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▀▄\n░░░░░░░░░░░▌▌░▌▌░░░░░\n░░░░░░░░░░░▌▌░▌▌░░░░░\n░░░░░░░░░▄▄▌▌▄▌▌░░░░░\n");
	return 0;
}