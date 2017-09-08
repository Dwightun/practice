#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void GenerateString(int x, char *s1){
	int i;
	char* s2;
	s2 = (char*)malloc(sizeof(char)*(1<<(x-1)));
	
	for (i=1;i<x;i++)
		{
			strcpy(s2,s1);
			s2[strlen(s1)] = 'a' + i;
			strcat(s2,s1);
			strcpy(s1,s2);
		}
	free(s2);
}

int main(){
	int x;
	char* s1;
	scanf("%d",&x);
	s1=(char*)malloc(sizeof(char)*(1<<(x-1)));
	s1[0]='a';
	GenerateString(x,s1);
	printf("%s",s1);
	return 0;
}	
