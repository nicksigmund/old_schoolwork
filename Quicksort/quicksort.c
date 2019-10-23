#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void loadFile(const char* fname, int** arr, int* n);
void printArr(int* arr, int n, double q, double r);
int* pivot(int* left, int* right);
void quicksort(int* left, int* right);
int* randPivot(int* left, int* right);
void quicksort_r(int* left, int* right);
void swap(int* l, int* r);
void writeFile(int* arr, int n);
void makeBestCase(int* arr, int* n);

int main(int argc, char** argv){
	if(argc != 2){
		perror("needs exactly 1 arguement!\n");
		exit(-1);
	}
	int *arr;
	int n = 0;
	if(! atoi(argv[1])){
		if(strcmp(argv[1], "0")){
			perror("Need a value > 0, or a file to read!");
		}
		printf("reading from \'%s\'\n", argv[1]);
		loadFile(argv[1], &arr, &n);
	}
	else{
		n = (int)(atoi(argv[1]));
		if (n <= 0){
			perror("Need a value > 0, or a file to read!");
		}
		arr = calloc(n, sizeof(int));
		srand(time(0));
		printf("number of inputs = %d\n",n);
		for(int i = 0; i < n; i++){
			arr[i] = rand();
			//printf("%d \n",arr[i]);
		}
		//writeFile(arr, n);
	}
	arr[n] = '\0';
	// copies array to be sorted, so that both sorting functions sort the same starting array
	int* arr2 = malloc(n * sizeof(int));
	memcpy(arr2, arr, n * sizeof(int));
	//printf("copied arr:\n");
	//printArr(arr2, n);

	clock_t start, end;
	double quick_time, rand_time;

	printf("running quicksort... \n");
	//printArr(arr, n);
	start = clock();		// Start timer for quicksort
	quicksort(&arr[0], &arr[n-1]);
	end = clock();			// end timer for quicksort
	quick_time = ((double)(end - start))/CLOCKS_PER_SEC;
	printf("running randomized quick sort... \n");
	//printArr(arr, n);
	start = clock();		// start timer for random quicksort
	quicksort_r(&arr2[0], &arr2[n-1]);
	end = clock();			// end timer for random quicksort
	rand_time = ((double)(end - start))/CLOCKS_PER_SEC;
	//printf("Qucksort_r:  \n");
	//printArr(arr, n);
	//printf("Qucksort time:  %fsec\nRandQuicksort time: %fsec\n", quick_time, rand_time);
	printArr(arr, n, quick_time, rand_time);
	printf("Qucksort time:  %fsec\nRandQuicksort time: %fsec\n", quick_time, rand_time);

	//makeBestCase(arr2,  &arr2[n - 1]);
	//writeFile(arr2, n);

	return 0;
}

void makeBestCase(int* arr, int* n){
	// swaps the middle and last of the array, and of each 'middle' pivot
	// so that quicksort will have the best possible pivot points.
	// only works with an already sorted array.
	if( n - arr <= 0)
		return;
	int offset = n - arr;
	offset /= 2;
	//printf("offset: %d\n",offset);
	int* mid = arr + offset;
	swap(n, mid);
	makeBestCase(arr + 1, mid - 1);
	makeBestCase(mid + 1, n - 1);
}

void writeFile(int* arr, int n){
	char fname[25];
	sprintf(fname,"best%d.txt",n);
	FILE *out = fopen(fname, "w");

	for(int i = 0; i < n; i++){
		fprintf(out, "%d\n", arr[i]);
	}
	fclose(out);
}

void loadFile(const char* fname, int** array, int* n){
	FILE *in;
	in = fopen(fname, "r");

	puts(fname);
	int i = 10;
	int *arr = *array;
	arr = malloc(i * sizeof(int));
	
	while(fscanf(in,"%d", &arr[(*n)++]) == 1){
		if(i - *n <= 5){
			i *= 2;
			arr = realloc(arr, i * sizeof(int));
		}
		//printf("%d: %d\n",*n - 1,arr[(*n)-1]);
	}
	
	(*n)--;
	arr[(*n)] = '\0';
	fclose(in);

	*array = arr;

}
void swap(int* l, int* r){
	int tmp = *l;
	*l = *r;
	*r = tmp;
}

void printArr(int *arr, int n, double q, double f){
	char fname[25];
	sprintf(fname,"sorted%d.txt",n);
	FILE *out = fopen(fname,"w");

	//printf("%f %f\n",q, f);
	
	//fprintf(out, "Quicksort:  %fsec\nRandomized:  %fsec\n\n");
	for(int i = 0; i < n; i++){
		fprintf(out, "%d\n",arr[i]);
	}
	fclose(out);
	//puts("");
}

int* randPivot(int* left, int* right){
	srand(time(NULL));
	int offset = rand() % (right - left);
	int* r = left + offset;
	swap(r, right);
	return pivot(left, right);
}

int* pivot(int* left, int* right){
	int piv = *right;
	int* low = left;
	int* high = right - 1;
	int tmp = 0;
	while(1){
		while(*low < piv && low++ < high){
			;
		}
		while(*high > piv && high-- > low){
			;
		}
		if(low >= high){
			break;
		}
		else{
			swap(low, high);
		}
	}
	swap(low, right);
	
	return low;

}

void quicksort(int* left, int* right){
	int *part;
	if(right <= left)
		return;
	else{


		part = pivot(left, right);
		quicksort(left, part - 1);
		quicksort(part + 1, right);
	}
}

void quicksort_r(int* left, int* right){
	int* part;
	if(right <= left)
		return;
	else{
		part = randPivot(left, right);
		//part = pivot(left,right);
		quicksort_r(left, part - 1);
		quicksort_r(part + 1, right);
	}
}