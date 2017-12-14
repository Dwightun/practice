#include "h.h"

int main(int argc, char** argv){
    key_t key = ftok("m.txt", 0);
    int msg_id;
    printf("%d\n",key);
    if((msg_id = msgget(key, 0666 | IPC_CREAT)) == -1){
        printf("no server\n");
        exit(1);
    }
    answer_t answer;
    int a = 0;
    int b = 0;
    pid_t pid;
    request_t request;
    request.type = 1;
    scanf("%d%d", &request.a, &request.b);
    request.user_id = getpid();
    msgsnd(msg_id, &request, sizeof(request), 0);
    msgrcv(msg_id, &answer, sizeof(answer), pid, 0);
    printf("ans = %d\n", answer.c);
    return 0;
 }