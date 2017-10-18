/*some test
N t size
1 9.293 1000
1 9.401 1000
2 5.800 1000
2 5.783 1000
3 4.506 1000
3 4.655 1000
4 4.089 1000
4 4.064 1000
t = 9,1 * pow(N, -0,61); this is the dependence of time from N
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
//this structure contains our matrices and size of it
typedef struct {
	int size;
	float *a, *b, *c;
} matrix_t;
//this structure contains the way of order of multiplying
typedef struct {
	int threadnum;
	int count_of_thread;
	matrix_t* res;
} order_t;

void* calc_routine(void* arg); //this function use dot product to calculate single cell and put it in this cell
float* generate_empty_matrix(int size); //clear from signature :)
float* generate_and_fill_matrix(int size); //clear from signature :)
float dot_prod(matrix_t *matrix, int i, int j); //this function calculates dot product of column and string
void matrix_print(float *mat, int size); //this function calculate

int main(int argc, char** argv) {
	srand(time(NULL)); //I think this is  "THE KOCTb|Lb" (also used to generate really random numbers)
	if (argc < 2 || argc > 3)
	{
		printf("R U RETARD?(input)\n");
		exit(-3);
	}
	int size = atoi(argv[1]);
	if (size < 1)
	{
		printf("R U RETARD?(size)\n");
		exit(-3);
	}
	int count_of_thread;
	if (argc == 3)
	{
		count_of_thread = atoi(argv[2]);
		if (count_of_thread < 1)
		{
			printf("R U RETARD?(count_of_thread)\n");
			exit(-3);
		}
	}else {
		count_of_thread = sysconf(_SC_NPROCESSORS_ONLN); // wow amazing func, such func
		if (count_of_thread < 1)
		{
			printf("SYS IS RETAR\n");
			count_of_thread = 2; // cause sys did give the count let's define it as 2
		}else{
			printf("count_of_thread = %d \n", count_of_thread);
		}
	}
	matrix_t res;
	res.size = size;
	res.a = generate_and_fill_matrix(size); //calloc+
	res.b = generate_and_fill_matrix(size);	//calloc+
	res.c = generate_empty_matrix(size);	//calloc+
	printf("SUDDENLY WE CREATED SOME MATRIXS\n");
	pthread_t *th = (pthread_t*)malloc(sizeof(pthread_t) * count_of_thread); //calloc +
	printf("NOW WE R GOING TO USE SOME THREADS\n");
	for (size_t i = 0; i < count_of_thread; i++){
		order_t* order = (order_t*)malloc(sizeof(matrix_t)); //calloc *n
		matrix_t* local_matrix = malloc(sizeof(matrix_t));	//calloc *n
		local_matrix->a = generate_empty_matrix(size);
		memcpy(local_matrix->a, res.a, sizeof(float) * size * size);
		local_matrix->b = generate_empty_matrix(size);
		memcpy(local_matrix->b, res.b, sizeof(float) * size * size);
		local_matrix->size = size;
		local_matrix->c = res.c;
		//wow we got some copies
		order->res = local_matrix;
		order->threadnum = i;
		order->count_of_thread = count_of_thread;
		//did order list
		int start_status = pthread_create(&th[i], NULL, calc_routine, order);
		if (start_status != 0)
		{
			printf("\n");
			exit(-3);
		}
	}
	for (int i = 0; i < count_of_thread; i++)
	{
		pthread_join(th[i], NULL);
	}
	matrix_print(res.a, size);
	printf("-----------------------------\n");
	matrix_print(res.b, size);
	printf("-----------------------------\n");
	matrix_print(res.c, size);
	free(res.a);
	free(res.b);
	free(res.c);
	free(th);
	exit;
}

void* calc_routine(void* arg) {
	order_t* order = (order_t*)arg;
	int size = order->res->size;
	for (int i = order->threadnum; i < size; i += order->count_of_thread) {
		for (int j = 0; j < size; ++j) {
			*(order->res->c + i*size + j) = dot_prod(order->res, i, j);
		}
	}
	return NULL;
}

float* generate_empty_matrix(int size) {
	float* matrix = (float*)calloc(size * size, sizeof(float));
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			*(matrix + i*size + j) = 0;
		}
	}
	return matrix;
}

float* generate_and_fill_matrix(int size) {
	float* matrix = generate_empty_matrix(size);
	if (matrix == NULL) {
		return NULL;
	}
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			*(matrix + i*size + j) = rand()/100000000; //didn't find a good way to generate random numbers for each single execution of programm
		}
	}
	return matrix;
}

float dot_prod(matrix_t *matrix, int i, int j) {
	int size = matrix->size;
	int result = 0;
	for (int k = 0; k < size; k++){
		result += *(matrix->a + i * size + k) * *(matrix->b + k * size + j);
	}
	return result;
}


void matrix_print(float *mat, int size){
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%1.3g ", *(mat+size*i + j));
		}
		printf("\n");
	}
}	
