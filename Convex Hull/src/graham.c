// graham.c

#include "../inc/graham.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


int pivot(struct CoordArr *arr, int l, int r, struct Coord ref){
	struct Coord piv = arr->coords[r];
	int low = l;
	int high = r - 1;
	
	while(1){
		while(coordCmp(arr->coords[low], piv, ref) < 0 && low++ < high){
			;
		}
		while(coordCmp(arr->coords[high], piv, ref) > 0 && high-- > low){
			;
		}
		if(low >= high){
			break;
		}
		else{
			coordSwap(arr, low, high);
		}
	}

	coordSwap(arr, low, r);
	
	return low;

}

void quicksort(struct CoordArr *arr, int l, int r, struct Coord ref){
	int part;
	if(l < r){
		part = pivot(arr, l, r, ref);
		quicksort(arr, l, part - 1, ref);
		quicksort(arr, part + 1, r, ref);
	}
}

struct CoordArr graham(struct CoordArr arr){
	struct CoordArr hull;
	hull.m = 0;
	hull.n = 0;

	struct Coord min;
	struct Coord cur;
	
	bottomPointToZero(&arr);
	struct Coord ref = arr.coords[0];

	
	//printCoordArr(arr);
	quicksort(&arr, 1, arr.n - 1, ref);
	
	//printf("quicksort done...\n");
	
	//printCoordArr(arr);
	int n = 1;
	for(int i = 1; i < arr.n; i++){
		while(i < arr.n - 1 && orientation(ref, arr.coords[i], arr.coords[i + 1]) == 0)
			i++;

		arr.coords[n] = arr.coords[i];
		n++;
	}	

	arr.n = n;
	//printCoord(p);
	//printCoordArr(arr);
	//puts("\n");

	for (int i = 0; i < 3; ++i)
		insertCoord(&hull, arr.coords[i]);
	
	for(int i = 3; i < n; i++){
		while(orientation(hull.coords[hull.n - 2], hull.coords[hull.n - 1], arr.coords[i]) >= 0)
			pop(&hull);
		insertCoord(&hull, arr.coords[i]);
	}


	return hull;
}