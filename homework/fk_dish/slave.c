#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h> 
#include <string.h> 
/*
timew.txt - wash time
timep.txt  - dry time
w.txt - dirty dishes
table.txt - table means table
*/

#define THREADS_COUNT 2
#define TABLE_LIMIT 10 // table size
#define DISHES_NAME 20 // max dish size
#define QUANITY 100 // max number of dirty dishes
int TABLE = 0;

struct sembuf mybuf;
typedef struct dishes { // struct for dirty
	char name[DISHES_NAME];
	int qua;
} dishes_t;
typedef struct ptime { // local data for operating dishes
	char name[DISHES_NAME];
	int t;
} ptime_t;

int semid = -1;
FILE *table;

void SemOp(int sem_num, int n)
{
	mybuf.sem_num = sem_num;
	mybuf.sem_op = n;
	mybuf.sem_flg = 0;
}

int wait(int j) {
	mybuf.sem_num = j;
	mybuf.sem_flg = 0;
	return mybuf.sem_op;
}


void* washer(void* dummy) {
	FILE *time_file, *w_file;
	ptime_t timew[QUANITY];
	dishes_t load[QUANITY];
	int i = 0;
	int b = 0;
	char str[DISHES_NAME];
	time_file = fopen("timew.txt", "r");
	while (fscanf(time_file, "%s%d", timew[i].name, &(timew[i].t)) != EOF) {
		i++;
	}
	fclose(time_file);
	i = 0;
	w_file = fopen("w.txt", "r");
	while (fscanf(w_file, "%s%d", load[i].name, &(load[i].qua)) != EOF) {
		i++;
	}
	int y = 0;
	for (y = 0; y < i; y++) {
		int k = 0;
		while (strcmp(load[y].name, timew[k].name) != 0) {
			k++;
		}
		k = timew[k].t;
		for (int q = load[y].qua; q > 0; q--) {
			sleep(k);
			while (1) {
				if (TABLE_LIMIT > TABLE) {
					if (wait(0) != -1) {
						SemOp(1, -1);
						fseek(table, 0, SEEK_SET);
						for (int e = 0; e < (b + 1); e++) {
							fscanf(table, "%s", str);
						}
						fputs(load[y].name, table);
						fputs("\n", table);
						SemOp(1, 1);
						break;
					}
				}
			}
			TABLE++;
			b++;
			printf("%s is washed and placed \n", (load[y].name));
		}
	}
	while (1) {
		fseek(table, 0, SEEK_SET);
		for (int e = 0; e < (b + 1); e++) {
			fscanf(table, "%s", str);
		}
		fputs("ALL", table);
		fputs("\n", table);
		TABLE++;
		SemOp(1, 1);
		break;
	}
	fclose(w_file);
	return NULL;
}


void* wiping(void* dummy) {
	FILE *time_file;
	ptime_t timep[QUANITY];
	int i = 0;
	int k = 0;
	int b = 0;
	char str[DISHES_NAME];
	time_file = fopen("timep.txt", "r");
	while (fscanf(time_file, "%s%d", timep[i].name, &(timep[i].t)) != EOF) {
		i++;
	}
	fclose(time_file);
	while (1) {
		if (TABLE < 100) {
			SemOp(0, 1);
		}
		if ((TABLE > 0) && (wait(0) > -1)) {
			SemOp(0, -1);
			fseek(table, b, SEEK_SET);
			fscanf(table, "%s", str);
			b = b + strlen(str) + 1;
			SemOp(0, 1);
			if (strcmp(str, "ALL") == 0) {
				exit(-1);
			}
			else {
				while (strcmp(str, timep[k].name) != 0) {
					k++;
				}
				TABLE--;
				int j = timep[k].t;
				sleep(j);
				printf("%s is wiped \n", (timep[k].name));
				k = 0;
			}
		}
	}
	return NULL;
}

int main() {
	char pathname[] = "dummy.txt";
	key_t key = ftok(pathname, 0);
	if ((semid = semget(key, 2, 0666 | IPC_CREAT)) < 0) {
		printf("Can\'t get semid\n");
		exit(-1);
	}
	SemOp(0, 1);
	SemOp(1, 1);
	table = fopen("table.txt", "w+");
	pthread_t thread_ids[THREADS_COUNT];
	pthread_create(&thread_ids[0], (pthread_attr_t *)NULL, &washer, table);
	pthread_create(&thread_ids[1], (pthread_attr_t *)NULL, &wiping, table);
	int i;
	for (i = 0; i < THREADS_COUNT; ++i) {
		pthread_join(thread_ids[i], (void **)NULL);
	}
	fclose(table);
	return 0;
}
