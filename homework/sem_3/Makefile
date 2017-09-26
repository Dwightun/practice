all: cpu

cpu: main_arg.o func.o
		gcc -o $@ -g $^

main_arg.o: main_arg.c
		gcc -c main_arg.c

func.o: func.c
		gcc -c func.c