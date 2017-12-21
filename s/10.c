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
 
void myop(int id, int val) { //функция оператор семафора
	struct sembuf sb;
	sb.sem_flg = 0;
	sb.sem_num = 0;
	sb.sem_op = val;
	semop(id, &sb, 1);
}


int main() {
	int desk = ftok("jojo", 0);
	int semid_1 = semget(desk, 1, S_IRUSR | S_IWUSR | IPC_CREAT);
	semctl(semid_1, 0, SETVAL, 0);
	// создан семафор
	pid_t pid;
	pid = fork();
	if (pid == 0) {
		myop(semid_1, -1);
		sleep(1); //sleep для коректной печати 
		printf("░▄▀▌░░░▀▀░░▌▐░░░▀▀░░▌▒▀▒█▌\n░▌▒▀▄░░░░▄▀▒▒▀▄░░░▄▀▒▒▄▀▒▌\n░▀▄▐▒▀▀▀▀▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒█\n░░░▀▌▒▄██▄▄▄▄████▄▒▒▒▒█▀\n░░░░▄██████████████▒▒▐▌\n░░░▀███▀▀████▀█████▀▒▌\n░░░░░▌▒▒▒▄▒▒▒▄▒▒▒▒▒▒▐\n░░░░░▌▒▒▒▒▀▀▀▒▒▒▒▒▒▒▐/n");
		exit(0);
	}
	else {
		myop(semid_1, 1);
		printf("▄███████▀▀▀▀▀▀███████▄\n░▐████▀▒ЗАПУСКАЕМ▒▀██████▄\n░███▀▒▒▒▒▒ДЯДЮ▒▒▒▒▒▒▀█████\n░▐██▒▒▒▒▒▒БОГДАНА▒▒▒▒▒████▌\n░▐█▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████▌\n░░█▒▄▀▀▀▀▀▄▒▒▄▀▀▀▀▀▄▒▐███▌\n░░░▐░░░▄▄░░▌▐░░░▄▄░░▌▐███▌\n░▄▀▌░░░▀▀░░▌▐░░░▀▀░░▌▒▀▒█▌\n");
	}
	waitpid(pid, NULL, 0);
	return 0;
}