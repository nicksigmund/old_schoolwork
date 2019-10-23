// jarvic.c

#include "../inc/jarvis.h"
#include <stdio.h>
#include <stdlib.h>

struct CoordArr jarvic(struct CoordArr arr){
	if(arr.n < 3){
		perror("Need at least three points!");
		exit(-1);
	}

	struct CoordArr hull;
	hull.n = 0;
	hull.m = 0;

	bottomPointToZero(&arr);
	
	
	int q = -1;		// need to start at !0 so the loop starts
	for(int p = 0; p < arr.n && q != 0; p = q){
		insertCoord(&hull, arr.coords[p]);

		q = p + 1;

		for(int i = 0; i < arr.n; i++)
			if(orientation(arr.coords[p], arr.coords[i], arr.coords[q]) < 0)
				q = i;
	}
	return(hull);
}