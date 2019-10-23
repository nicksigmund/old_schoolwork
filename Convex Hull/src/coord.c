// coord.c

#include "../inc/coord.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>



void insertCoord(struct CoordArr *arr, struct Coord p){
	if (arr->n == 0){
		arr->coords = malloc(sizeof(struct Coord) * 20);
		arr->m = 20;
	}else if (arr->n >= arr->m -5){
		arr->coords = realloc(arr->coords, sizeof(struct Coord) * 2*arr->n);
		arr->m = 2 * arr->n;
	}
	arr->coords[arr->n++] = p;
}

double coordDistance(struct Coord a, struct Coord b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void coordSwap(struct CoordArr *arr, int a, int b){
	struct Coord tmp = arr->coords[a];
	arr->coords[a] = arr->coords[b];
	arr->coords[b] = tmp;
	//printf("Swapping %d with %d\n", a, b);
}

int coordCmp(struct Coord a,struct Coord b, struct Coord ref){
	
	int orient = orientation(ref, a, b);
	if(orient == 0)
		if(coordDistance(ref, a) >= coordDistance(ref, b))
			return 1;
		else
			return -1;
	else if(orient < 0)
		return -1;
	return 1;

}


struct Coord pop(struct CoordArr *arr){
	return arr->coords[arr->n-- - 1];

}

int sameCoord(struct Coord a, struct Coord b){
	if(a.x == b.x && a.y == b.y)
		return 1;
	return 0;
}

struct Coord randomCoord(){
	struct Coord p;
	p.x = rand() % 2000;
	p.y = rand() % 2000;
	//printCoord(p);
	return p;
}

struct CoordArr randomCoordArr(int n){
	struct CoordArr arr;
	arr.coords = malloc(sizeof(struct Coord) * n);
	srand(time(0));
	FILE *out = fopen("r.txt", "w");
	for (int i = 0; i < n; i++){
		arr.coords[i] = randomCoord();
		fprintf(out, "%d %d\n",arr.coords[i].x, arr.coords[i].y);
		//printCoord(arr.coords[i]);
	}
	fclose(out);
	arr.n = n;
	arr.m = n;
	return arr;
}

void printCoord(struct Coord p){
	printf("(%d,%d)\n",p.x,p.y);
}

void printCoordArr(struct CoordArr arr){
	printf("m: %d\nn: %d\n",arr.m, arr.n);
	for(int i = 0; i < arr.n; i++)
		printCoord(arr.coords[i]);
}

void printHull(struct CoordArr arr){
	for(int i = 0; i < arr.n; i++)
		printf("(%d,%d)\n", arr.coords[i].x, arr.coords[i].y);
	
}

struct CoordArr fileCoords(const char* fname){
	FILE *in;
	in = fopen(fname, "r");

	struct CoordArr arr;
	int x, y;
	struct Coord p;
	while(fscanf(in, "%d",&x) == 1){
		fscanf(in, "%d", &y);
		p.x = x;
		p.y = y;
		insertCoord(&arr, p);
		//printCoord(p);
	}
	return arr;
}

void copyCoordArr(struct CoordArr arr, struct CoordArr *cpy){
	int n = arr.n;
	int m = arr.m;
	cpy->coords = malloc(sizeof(struct Coord) * n);
	memcpy(cpy->coords, arr.coords, n * sizeof(struct Coord));
	cpy->m = m;
	cpy->n = n;
}

int orientation(struct Coord p1, struct Coord p2, struct Coord p3){
	  return (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
	}

void bottomPointToZero(struct CoordArr *arr){
	struct Coord cur;
	struct Coord min;

	for(int i = 1; i < arr->n; i++){
		min = arr->coords[0];
		cur = arr->coords[i];
		if(cur.x < min.x){
			coordSwap(arr, i, 0);
		}else if (cur.x == min.x){
			if(cur.y < min.y)
				coordSwap(arr, i, 0);
		}
	}
}