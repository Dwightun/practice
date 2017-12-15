#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct mymsgbuf {
	long type;
	long return_id;
	int a;
	int b;
	int ans;
} mybuf_t;

int main() {
	int msq_id;
	char pathname[] = "jojo";
	key_t key;
	int i;
	int strlen;

	if ((key = ftok(pathname, 0)) < 0) {
		printf("no key :(\n");
		exit(-1);
	}
	if ((msq_id = msgget(key, 0666 | IPC_CREAT)) < 0) {
		printf("no msq_id :(\n");
		exit(-1);
	}
	mybuf_t mybuf;
	mybuf.type = 1;
	printf("?/n");
	scanf("%d%d", &mybuf.a, &mybuf.b);
	mybuf.return_id = getpid();
	strlen = sizeof(mybuf);
	if (msgsnd(msq_id, (struct msgbuf *) &mybuf, strlen, 0) < 0) {
		printf("no send :(\n");
		msgctl(msq_id, IPC_RMID, NULL);
		exit(-1);
	}
	if ((strlen = msgrcv(msq_id, (struct msgbuf *) &mybuf, sizeof(mybuf), getpid(), 0) < 0)) {
		printf("no recive :(\n");
		exit(-1);
	}
	printf("ans = %d\n", mybuf.ans);
	return 0;
}
