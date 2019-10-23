#include "../inc/coord.h"
#include "../inc/quickhull.h"
#include "../inc/jarvis.h"
#include "../inc/graham.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Prints convex hull to a file "set[number of points].txt"
void foutHull(struct CoordArr arr, int n, double q, double j, double g);

int main(){
	struct CoordArr arr;
	char resp;
	char fname[25];
	int n = 0;
	char *newln = NULL;
	size_t t;
	while(1){
		resp = '\0';
		printf("PROJ2 MENU\n(r):	RANDOM\n(f):	FILE\n(e):	EXIT\n");
		if((resp = getc(stdin)) == 0 || resp != 'r' && resp != 'e' && resp != 'f'){
			puts("That is not a valid response, please try again...");
			getline(&newln, &t, stdin);	// Clears stdin
		} else
			break;
	}

	if(resp == 'e'){
		puts("Bye!");
		exit(0);
	} else if (resp == 'f'){
		puts("What is the file name?");
		fscanf(stdin,"%s",&fname);
		printf("Will open file:  %s\n",fname);
		arr = fileCoords(fname);
		//printCoordArr(arr);
	} else if (resp == 'r'){
		puts("how many points?");
		fscanf(stdin, "%d", &n);
		arr = randomCoordArr(n);
		//printCoordArr(arr);
	}
	else
		exit(-1);

	n = arr.n;

	struct CoordArr arr2, arr3; //copies for the three algorithms
	copyCoordArr(arr, &arr2);
	copyCoordArr(arr, &arr3);

	clock_t start, end;
	double qh, jm, gs;


	//puts("quickhull...");
	start = clock();
	struct CoordArr q = quickhull(arr);
	end = clock();
	qh = ((double)(end - start))/CLOCKS_PER_SEC;
	//rmDuplicates(q);
	//printHull(q);

	//puts("jarvic...");
	start = clock();
	struct CoordArr j = jarvic(arr2);
	end = clock();
	jm = ((double)(end - start))/CLOCKS_PER_SEC;
	//printHull(j);

	//puts("graham...");
	start = clock();
	struct CoordArr g = graham(arr3);
	end = clock();
	gs = ((double)(end - start))/CLOCKS_PER_SEC;
	//printHull(g);

	//worstCaseHull();

	printf("G: %f\nJ: %f\nQ: %f\n", gs, jm, qh);

	foutHull(g, n, qh, jm, gs);

	return 0;
}

void foutHull(struct CoordArr hull, int n, double q, double j, double g){
	char fname[25];
	sprintf(fname,"set%d.txt",n);
	FILE *out = fopen(fname, "w");

	fprintf(out, "%s\nGraham Scan:	%fs\nJarvis March:	%fs\nQuick Hull:		%fs\n",fname,g,j,q);

	for(int i = 0; i < hull.n; i++){
		fprintf(out, "%4d	%4d\n", hull.coords[i].x, hull.coords[i].y);
	}
	fclose(out);
}

