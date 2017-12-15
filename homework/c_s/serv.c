#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREAD 2


typedef struct mymsgbuf {
	long type;
	long return_id;
	int a;
	int b;
	int ans;
} mybuf_t;

typedef struct{
	long type;
	long return_id;
	int a;
	int b;
	int msq_id;
	int sem_id;
} thread_buf_t;

void sem_op(int sem_id, int op) {
	struct sembuf sb;
	sb.sem_op = op;
	sb.sem_flg = 0;
	sb.sem_num = 0;
	semop(sem_id, &sb, 1);
}
void* processRequest(void* buf) {
	printf("Started%d\n", (((thread_buf_t*)buf)->return_id));
	mybuf_t mybuf;
	mybuf.ans = ((thread_buf_t*)buf)->a * ((thread_buf_t*)buf)->b;
	mybuf.type = ((thread_buf_t*)buf)->return_id;
	mybuf.return_id = 1;
	sleep(5);
	if (msgsnd(((thread_buf_t*)buf)->msq_id, (mybuf_t*)&mybuf, sizeof(mybuf), 0) < 0) {
		printf("nos send message to queue\n");
		msgctl(((thread_buf_t*)buf)->msq_id, IPC_RMID, NULL);
		exit(-1);
	}
	free(buf);
	printf("Finished %d\n", ((thread_buf_t*)buf)->return_id);
	sem_op(((thread_buf_t*)buf)->sem_id, 1);

	return NULL;
}
int main()
{
	int msq_id, sem_id;
	char pathname[] = "jojo";
	key_t key;
	int len, maxlen;
	mybuf_t mybuf;

	if ((key = ftok(pathname, 0)) < 0) {
		printf("no key\n");
		exit(-1);
	}


	if ((msq_id = msgget(key, 0666 | IPC_CREAT)) < 0) {
		printf("no msq_id\n");
		exit(-1);
	}

	if ((sem_id = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
		printf("no sem_id\n");
		exit(-1);
	}
	semctl(sem_id, 0, IPC_RMID);
	if ((sem_id = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
		printf("no sem_id\n");
		exit(-1);
	}

	sem_op(sem_id, MAX_THREAD);
	while (1) {
		mybuf.return_id = 0;
		if ((len = msgrcv(msq_id, (struct msgbuf *) &mybuf, sizeof(mybuf), 1, 0) < 0)) {
			printf("Can\'t receive message from queue\n");
			exit(-1);
		}
		if (mybuf.return_id) {
			thread_buf_t* buf;
			buf = malloc(sizeof(thread_buf_t));
			memcpy(buf, &mybuf, sizeof(mybuf));
			buf->msq_id = msq_id;
			buf->sem_id = sem_id;
			pthread_t th;
			sem_op(sem_id, -1);
			pthread_create(&th, NULL, processRequest, buf);
		}

	}
	return 0;
}
