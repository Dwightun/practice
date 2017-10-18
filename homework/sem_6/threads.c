#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void* func(void *ar){
	int* myar = (int*)ar;
	for(int i = 0;i < 10000000; i++){
		myar[0]++;
		myar[1]++;
	}
}

int main(){
	pthread_t th;
	int ar[3];
	ar[0] = 0;
	ar[1] = 0;
	ar[2] = 0;
	int status = pthread_create(&th, NULL, func, (ar + 1));
	func(ar);
	
	pthread_join(th, NULL);
	for (int i = 0; i < 3; i++)
	{
		printf("%d\n", ar[i]);
	}
	return 0;
}
