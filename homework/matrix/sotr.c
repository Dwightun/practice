#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef int(*myf)(int,int);

void swap(int* data1, int* data2){
	int buff;
	buff = *data1;
	*data1 = *data2;
	*data2 = buff;
}

int cmp_inc(int data1, int data2){
		return data1 > data2;
}

int cmp_dec(int data1, int data2){
		return !(data1 > data2);
}
	
void sort(int* array, int size, myf cmp_my){
	for(int i = 0; i + 1 < size; i++) {
		for(int j = i + 1; j < size; j++) {
			if(cmp_my(array[i], array[j])) {
				swap(&array[i], &array[j]);
			}
		}
	}
}

int main(){
	int a[10];
	for (int i = 0; i < 10; i++)
	{
		a[i] = 100 - i;
		printf("a[%d] = %d\n",i,a[i]);
	}
	printf("\n");
	sort(a, 10, cmp_inc);
	for (int i = 0; i < 10; i++)
	{
		printf("a[%d] = %d\n",i,a[i]);
	}
	printf("\n");
	sort(a, 10, cmp_dec);
	for (int i = 0; i < 10; i++)
	{
		printf("a[%d] = %d\n",i,a[i]);
	}
	return 0;
}
