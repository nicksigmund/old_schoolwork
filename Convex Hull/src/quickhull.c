// Quickhull.c
#include "../inc/quickhull.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI acos(-1.0)



struct CoordArr quickhull(struct CoordArr arr){
	struct CoordArr hull;
	if (arr.n < 3){
		perror("There must be at least 3 points for a convex hull...");
		return hull;
	}
	
	hull.m = 0;
	hull.n = 0;
	
	
	int max = 0;
	int min = 0;

	for(int i = 1; i < arr.n; i++){
		if(arr.coords[i].x < arr.coords[min].x)
			min = i;
		if(arr.coords[i].x > arr.coords[max].x)
			max = i;
	}

	findHull(arr, &hull, arr.coords[min], arr.coords[max], 1);
	findHull(arr, &hull, arr.coords[min], arr.coords[max], -1);

	return hull;
}

void findHull(struct CoordArr arr, struct CoordArr *hull, struct Coord point1, struct Coord point2, int side){
	//puts("findHull...");
	int orthog = 0;
	int max = 0;
	int m = 0;

	for(int i = 0; i < arr.n; i++){
		// a higher magnitude of orientation relates to a higher 
		// orthoginal distance of the middle point to the line 
		// segment formed by p1 and p3
		orthog = orientation(point1, arr.coords[i], point2);
		
		if((orthog ^ side) > 0 && abs(orthog) > max){
			max = abs(orthog);
			m = i;
		}
	}

	if (max == 0){
		
		insertCoord(hull, point1);
		insertCoord(hull, point2);
		//puts("found a point on the hull!");
		return;
	}

	findHull(arr, hull, arr.coords[m], point1, orientation(point2, arr.coords[m], point1));
	findHull(arr, hull, arr.coords[m], point2, orientation(point1, arr.coords[m], point2));
}

struct CoordArr rmDuplicates(struct CoordArr arr){
	struct CoordArr tmp;
	tmp.m = 0;
	tmp.n = 0;
	
	for(int i = 0; i < arr.n; i++)
		arr.coords[i].null = 0;
	for(int i = 0; i < arr.n - 1; i++)
		for(int j = i+1; j < arr.n; j++){
			if(sameCoord(arr.coords[i], arr.coords[j]) == 1 && arr.coords[i].null == 0 && arr.coords[j].null == 0){
				//printf("i.null:%d, j.null:%d\n", arr.coords[i].null, arr.coords[j].null);
				insertCoord(&tmp, arr.coords[j]);
				arr.coords[j].null = 1;
				arr.coords[i].null = 1;
				break;
			}
		}

	return tmp;
}

void worstCaseHull(){
	struct Coord l;
	struct Coord r;
	int div = 4;
	l.x = 0;
	l.y = 1000;
	r.x = 1000;
	r.y = 0;

	int x = 1, y = 0;

	FILE *out = fopen("worstcase.txt", "w");

	fprintf(out, "%d, %d\n%d %d\n",l.x, l.y, r.x, r.y);


	while(x < 1000 ){
		x = 1000*cos(PI/div);
		y = 1000*sin(PI/div);
		div *=2;
		fprintf(out, "%d %d\n", x, y);
	}

	fclose(out);
}
