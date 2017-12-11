#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#define N 1024



void sender(int sock, char* message);
void receiver(int sock, char* message);

int main(){
    char message[N];
    int sock;
    struct sockaddr_in addr;
    char num[2];
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3426); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("connect");
        exit(2);
    }
    recv(sock, num, N, 0);
    printf("your turn is %s\n", num);
    while(1){
        if(num[0]=='1'){
            sender(sock, message);
            receiver(sock, message);
        }else{
            receiver(sock, message);
            sender(sock, message);
        }
    }

    close(sock);

    return 0;
}

void sender(int sock, char* message){
    do{
    printf("enter your word\n<you>:");
    fflush(stdout);
    scanf("%s", message);
    //recv(sock, buf, N, 0);
    send(sock, message, strlen(message)+1, 0);
    recv(sock, message, 2, 0);
    switch(message[0]){
        case 'u':
            puts("Word already used");
            break;
        case 'z':
            puts("Not a word");
            break;
        case 'l':
            puts("R u a retard?");
            break;
    }
    }while(message[0]!='w');
}
void receiver(int sock, char* message){
    printf("waiting for other player\n");
    recv(sock, message, N, 0);
    printf("<other player>:%s\n", message);
}