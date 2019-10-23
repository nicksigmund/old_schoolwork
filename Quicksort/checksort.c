#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	if(argc != 2){
		perror("Feed me a file name!");
		exit(-1);
	}
	FILE *in = fopen(argv[1], "r");
	int sorted = 0;
	int cur = 0;
	int next = 0;
	char* buff = NULL;
	size_t n = 0;
	getline(&buff, &n, in);
	getline(&buff, &n, in);

	fscanf(in, "%d", &cur);
	while(fscanf(in, "%d", &next) == 1){
		if(cur > next){
			sorted = 1;
			printf("%d is not less than %d!\n", cur, next);
			break;
		}
		//printf("%d < %d\n", cur, next);
		cur = next;
	}

	fclose(in);


	if(sorted == 0){
		printf("Yay, it is a sorted file!\n");
	}
	else
		printf("You suck at sorting!\n");
}