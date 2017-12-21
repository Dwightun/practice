#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>

#define THREAD_NUM 4
#define DELTA 1000
#define A 0.0 		// начало интегрирования
#define B 2.0		// конец интегрирования

// DELTA - мелкость разбиения каждого отрезка (их THREAD_NUM штук), а значит общая мелкость будет DELTA * THREAD_NUM  

typedef struct {
	double a;
	double b;
	int thr_num;
	double sum;
}args_t;

void* Calculate(void *arg); // cобственно считает интеграл

int main(int argc, char** argv) {

	int i;
	pthread_t tid[THREAD_NUM];
	double delta = ((B - A) / THREAD_NUM);
	args_t args[THREAD_NUM]; // создаем массив структур дабы исключить одновременного обращения к памяти 
	// массив тредов
	for (i = 0; i < THREAD_NUM; i++) {
		args[i].sum = 0;
		args[i].a = A + i * delta;				// откуда
		args[i].b = A + (i + 1) * delta;			// докуда
		args[i].thr_num = i + 1;					// номер треда
		pthread_create(&tid[i], NULL, &Calculate, &args[i]);

	}
	for (i = 0; i < THREAD_NUM; i++)
		pthread_join(tid[i], NULL);
	double sum = 0;
	for (size_t i = 0; i < THREAD_NUM; i++) {
		sum += args[i].sum;
	}
	printf("%lf \n", sum);
	return 0;
}


void* Calculate(void *arg) {

	args_t *args = (args_t*)arg;
	double sum1 = 0;			// часть интеграла
	double y = (args->b - args->a) / DELTA;		// шаг интегрирования
	double x = args->a;				// по х идет суммирование
	while (x < args->b) {
		sum1 += sqrt(4 - x * x) * y;
		x += y;
	}
	args->sum += sum1;
	printf("%d) [%.2lf, %.2lf] sum = %lf \n", args->thr_num, args->a, args->b, sum1);
	return NULL;
}
