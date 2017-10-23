#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
//this structure contains our matrices and size of it
typedef struct {
	int size;
	float *a, *b, *c;
} matrix_t;
//this structure contains the way of order of multiplying
typedef struct {
	int threadnum;
/*
fixit: соблюдайте единый стиль: thread_num
*/
	int count_of_thread;
	matrix_t* res;
} order_t;

void* calc_routine(void* arg); //this function use dot product to calculate single cell and put it in this cell
float* generate_empty_matrix(int size); //clear from signature :)
float* generate_and_fill_matrix(int size); //clear from signature :)
float dot_prod(matrix_t *matrix, int i, int j); //this function calculates dot product of column and string
void matrix_print(float *mat, int size); //this function calculate

/*
fixit: из названия ф-и ожидается, что она вернет либо 1, если матрица была создана,
либо 0 в случае ошибки.
Либо переименуйте, либо измените её текущее поведение.
*/
void is_matrix_created(matrix_t matrix);

int main(int argc, char** argv) {
	srand(time(NULL)); //I think this is  "THE KOCTb|Lb" (also used to generate really random numbers)
	/*
	Если вы вносите изменения в свой код, и следите за тем, насколько это изменение ускорило код, то
	по-моему правильнее было бы написать 
	const int SEED = 123; // некое случайное число
	srand(SEED);
	тогда от запуску к запуску у вас будут генерироваться одни и те же матрицы (псевдослучайные),
	и вы будете смотреть, как изменения в алгоритме влияют на ускорение кода ...
	при фиксированных остальных параметрах
	*/
	if (argc < 2 || argc > 3)
	{
		perror("wrong amount of arguments");
		exit(-3);
	}
	int size = atoi(argv[1]);
	if (size < 1)
	{
		perror("wrong size of matrix");
		exit(-3);
	}
	int count_of_thread;
	if (argc == 3)
	{
		count_of_thread = atoi(argv[2]);
		if (count_of_thread < 1)
		{
			perror("wrong amount of threads");
			exit(-3);
		}
	}else {
		count_of_thread = sysconf(_SC_NPROCESSORS_ONLN); // wow amazing func, such func
		if (count_of_thread < 1)
		{
			perror("wrong amount of arguments");
			count_of_thread = 2; // cause sys did give the count let's define it as 2
		}else{
			printf("count_of_threads = %d \n", count_of_thread);
		}
	}
	matrix_t res;
	res.size = size;
	res.a = generate_and_fill_matrix(size); //calloc +
	res.b = generate_and_fill_matrix(size);	//calloc +
	res.c = generate_empty_matrix(size);	//calloc +
	is_matrix_created(res);
	//printf("SUDDENLY WE CREATED SOME MATRIXS\n");
	pthread_t *th = (pthread_t*)malloc(sizeof(pthread_t) * count_of_thread); //calloc +
	if (th == NULL){
		perror("unable to allocate memory for thread structure");
			exit(-3);
	}
	//printf("NOW WE R GOING TO USE SOME THREADS\n");
	for (size_t i = 0; i < count_of_thread; i++){
		order_t* order = (order_t*)malloc(sizeof(matrix_t)); //calloc *n
		if (order == NULL)
		{
			perror("unable to allocate memory for order");
			exit(-3);
		}
		/*
		fixit: непонятно, зачем копировать кучу раз исходные матрицы.
		можно обойтись без копий ... так и следует сделать
		*/
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
			perror("wrong amount of arguments");
			exit(-3);
		}
	}
	for (int i = 0; i < count_of_thread; i++)
	{
		pthread_join(th[i], NULL);
	}
	/*
	вероятно т.к. ваша цель измерить время работы умножения матриц от числа нитей,
	то вывод матриц на экран и другие вспомогательные операции нужно убрать/минимизировать
	*/
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
void is_matrix_created(matrix_t m) {
	if (m.a == NULL || m.b == NULL || m.c == NULL) {
		perror("failure with matrix creations");
		exit(-4);
	}
}

void* calc_routine(void* arg) {
	order_t* order = (order_t*)arg;
	int size = order->res->size;
	for (int i = order->threadnum; i < size; i += order->count_of_thread) {
		for (int j = 0; j < size; ++j) {
			/*
			fixit: пробелы вокруг *
			*/
			*(order->res->c + i*size + j) = dot_prod(order->res, i, j);
			/*
			FYI:
			https://stackoverflow.com/questions/20467117/for-matrix-operation-why-is-ikj-faster-than-ijk
			*/
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
			*(matrix + i*size + j) = rand()/100000000.0; //didn't find a good way to generate random numbers for each single execution of programm
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
			/*
			fixit: пробелы вокруг бинарных операторов
			*/
			printf("%1.3g ", *(mat+size*i + j));
		}
		printf("\n");
	}
}	
