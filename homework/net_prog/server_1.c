#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#define N 1024

char first_char;

int cmpfunc (const void * a, const void * b) {
   return ( -*(int*)a + *(int*)b );
}

unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

int did_it_use(char* word, int* used_words){
    int tmp = hash(word);
    int j = 0;
    for(int i = 0; i < N; i++){
        if(used_words[i] == tmp){
            return 1;
        }
        while(used_words[j] != 0){
            j++;
        }
        used_words[j] = tmp;
        return 0;
    }
}

int is_word_normal(char* word){
    for(int i = 0; i < strlen(word); i++){
        if( !('a' <= word[i] <= 'z') )
            return 0;
    }
    return 1;
}


int main(){

    int listener;
    struct sockaddr_in addr;
    char word_buf_2[1024];
    char word_buf_1[1024];
    int bytes_read;
    int offset = 0;
    int *used_words;
    int soc1, soc2;
    used_words = calloc(N, sizeof(int));
    used_words[0] = 228;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0){
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3426);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("bind");
        exit(2);
    }

    listen(listener, 2);
    while(1)
    {

        soc1 = accept(listener, NULL, NULL);
        soc2 = accept(listener, NULL, NULL);

        if((soc1 < 0) || (soc2 < 0)){
            perror("accept");
            exit(3);
        }

        char *good_boi_mes = "well done";
        char *used_word_mes = "used";
        char *wrong_word_mes = "wrong";
        char *first_letter_mes = "l-wrong";
        //send(soc1, 1, 1, 0);
        //send(soc2, 2, 1, 0);
        int work_1 = 0;
        int work_2 = 0;
        char first_l;
        char last_l;
        last_l = 'a';
        while(1)
        {
            work_1++;
            work_2++;
            while(work_1 != 0){
                bytes_read = recv(soc1, word_buf_1, 1024, 0);
                send(soc2, &word_buf_1[0], 2, 0);
                if(is_word_normal(word_buf_1) == 1){
                    if( last_l = word_buf_1[0] ){
                        if(did_it_use(word_buf_1, used_words) == 0){
                            last_l = word_buf_1[strlen(word_buf_1) - 1];
                            send(soc1, good_boi_mes, sizeof(good_boi_mes) + 1, 0);
                            send(soc2, word_buf_1, sizeof(word_buf_1) + 1, 0);
                            work_1--;
                        }else{
                            send(soc1, used_word_mes, sizeof(used_word_mes) + 1, 0);
                        }
                    }else{
                        send(soc1, first_letter_mes, sizeof(used_word_mes) + 1, 0);
                    }  
                }else{
                    send(soc1, wrong_word_mes, sizeof(wrong_word_mes) + 1, 0);
                }
                qsort(used_words, N, sizeof(int), cmpfunc);
            }
            while(work_2 != 0){
                bytes_read = recv(soc2, word_buf_2, 1024, 0);
                send(soc2, &word_buf_1[0], 2, 0);
                if(is_word_normal(word_buf_2) == 1){
                    if( last_l = word_buf_2[0] ){
                        if(did_it_use(word_buf_2, used_words) == 0){
                            last_l = word_buf_2[strlen(word_buf_2 - 1)];
                            send(soc2, good_boi_mes, sizeof(good_boi_mes) + 1, 0);
                            send(soc1, word_buf_2, sizeof(word_buf_2) + 1, 0);
                            work_2--;
                        }else{
                            send(soc2, used_word_mes, sizeof(used_word_mes) + 1, 0);
                        }
                        }else{
                            send(soc2, used_word_mes, sizeof(used_word_mes) + 1, 0);
                         }  
                }else{
                    send(soc2, wrong_word_mes, sizeof(wrong_word_mes) + 1, 0);
                }
                qsort(used_words, N, sizeof(int), cmpfunc);
            }
        }
    }
    close(soc1);
    close(soc2);
    return 0;
}