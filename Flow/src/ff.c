// ff.c
#include "../inc/ff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int FF(struct Graph g){
	int flow = 0;
	int update;
	int path[g.n];
	memset(path, 0, sizeof(path[0]) * g.n);

	while(BFS(&g, path)){
		update = INT_MAX;
		for(int i = g.n - 1; path[i] != 0; i = path[i]){
			update = (g.varr[path[i]][i] < update)? g.varr[path[i]][i] : update;
		}

		for(int i = g.n - 1; path[i] != 0; i = path[i]){
			g.varr[i][path[i]] += update;
			g.varr[path[i]][i] -= update;
		}
		flow += update;

	}

	return flow;
}