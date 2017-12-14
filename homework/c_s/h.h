#include <sys/sem.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define INITIAL_CHANNEL 1
#define QUEUE_CHANNEL 2
#define TERMINATE_VALUE 666
#define MSG_KEY 1
#define QUEUE_KEY 2

typedef struct request{
    int type;
    int a;
    int b;
    pid_t user_id;
} request_t;

typedef struct answer{
    int type;
    int c;
} answer_t;
