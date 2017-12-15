#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <string.h>

#define NAMESIZE 100
int h = 0;
typedef struct {
	char **path;
	int count;
}path_t;
void DFS(const char *s, int deep, const char *file, path_t *path) {
	DIR * hw;
	struct dirent *entry;
	h++;
	printf("Find %s in directory %s\n", file, s);
	if (h <= deep) {
		if ((hw = opendir(s)) == NULL) {
			fprintf(stderr, "Error\n");
			perror("Your error");
			return;
		}
		while ((entry = readdir(hw)) != NULL) {
			//printf("%ld - %s [%d] %d\n", entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);
			if (!strcmp(entry->d_name, file)) {
				printf("finded %s in dirctory ---------------------------------------%s\n", file, s);
				strcpy(path->path[path->count], s);
				path->count++;
			}
			if (entry->d_type == 4) {
				char new_dir[NAMESIZE];
				strcpy(new_dir, s);
				strcat(new_dir, "/");
				strcat(new_dir, entry->d_name);
				DFS(new_dir, deep - 1, file, path);
			}
		}
		closedir(hw);
	}
	h--;
}


int main(int argc, char** argv) {
	if (argc != 4) {
		fprintf(stderr, "Usage: %s directory search_of_depth name\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	path_t path;
	int deep1 = atoi(argv[2]);
	char directory[NAMESIZE];
	char file[NAMESIZE];
	strcpy(directory, argv[1]);
	strcpy(file, argv[3]);
	path.path = (char**)calloc(100, sizeof(char*));
	path.count = 0;
	for (int i = 0; i < 100; i++) {
		path.path[i] = (char*)calloc(NAMESIZE, sizeof(char));
	}
	DFS(directory, deep1, file, &path);
	for (int i = 0; i < path.count; i++) {
		printf("your obj in %s\n", path.path[i]);
	}

	return 0;
}
