all: matrix

matrix: matrix_mul.o
		gcc -o $@ -g $^ -lpthread

matrix_mul.o: matrix_mul.c
		gcc -c matrix_mul.c -lpthread