#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[]){
	char buff[1000];
	int x = open(argv[1], O_RDONLY);
	int s = read(x, buff, 1000);
	printf("%d\n", x);
	write(1,buff,s);
}
