
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void genln(char** prog, int* fd_in, int* fd_out){
	pid_t pid=fork();
	if(pid==0){
		if(fd_out!=NULL){
		printf("CLOSING STDOUT\n");
		close(STDOUT_FILENO);
		dup(fd_out[1]);
		close(fd_out[1]);
		close(fd_out[0]);
		}
		if(fd_in!=NULL){
		printf("CLOSING STDIN\n");
		close(STDIN_FILENO);
		dup(fd_in[0]);
		close(fd_in[0]);
		close(fd_in[1]);
		}
		printf("%s\n", prog[0]);
		execvp(prog[0], prog);
		
		exit(0);
	}
	
	
}
void splitspace(char* str, char** strss){
	char** saveptr;
	char* ret;
	int i=0;
	ret=strtok_r(str," ",saveptr);
	
	strss[0]=ret;
	printf("%x\n", strss[i]);
	for(i=1; i<10; i++){
		
		ret=strtok_r(NULL," ",saveptr);
		if(ret==NULL) break;
		strss[i]=ret;
	}
	
}
int main(int argc, char **argv)
{
	char*** strs;
	char** saveptr;
	char* ret;
	char del_1[2];
	del_1[0]='|';
	del_1[1]=0;
	int i=0;
	int j=0;
	saveptr=malloc(sizeof(void*));
	strs=calloc(10, sizeof(void*));
	ret=strtok_r(argv[1],del_1,saveptr);
	
	strs[i]=calloc(10, sizeof(void*));
	printf("calling splitspace\n");
	printf("%s\n", ret);
	splitspace(ret, strs[i]);
	printf("%x\n", strs[i][0]);
	printf("done\n");
	for (i=1; i<10; i++){
		ret=strtok_r(NULL,del_1,saveptr);
		if(ret==NULL) break;
		strs[i]=calloc(10, sizeof(void*));
		printf("calling splitspace\n");
		printf("%s\n", ret);
		splitspace(ret, strs[i]);
		printf("done\n");
	}
	int ** pipes;
	pipes=calloc(i, sizeof(void*));
	for(j=0; j<i-1; j++){
		 pipes[j]=calloc(2, sizeof(int));
		 
	}
	printf("allocated\n");
	int* last=NULL;
	for(j=0; j<i; j++){
		printf("cycle\n");
		if(pipes[j]!=NULL) pipe(pipes[j]);
		printf("calling genln\n");
		printf("%s\n", strs[j][0]);
		genln(strs[j], last, pipes[j]);
		printf("done\n");
		if(last!=NULL){
		close(last[0]);
		close(last[1]);
		}
		printf("rewriting last\n");
		last=pipes[j];
		
		
	}
	wait();
	return 0;
}

