// dinic.s
#include "../inc/dinic.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int dinic(struct Graph g){
	int flow = 0;
	int update = 0;
	//memcopy(cap, g.varr,);
	int* path = calloc(g.n, sizeof(int));
	while(BFS(&g, path)){
		//memset(path, 0, sizeof(path[0]) * g.n);
		do{
			update = pushFlow(&g, 0, INT_MAX);
			flow += update;
			if(update == 0){
				break;
			}
		}while(update > 0);

	}
	return flow;
}

int pushFlow(struct Graph *g, int start, int flow){
	if(start == g->n -1)
		return flow;

	int tmp, update;

	for(int v = 0; v < g->n; v++){
		int cap = g->varr[start][v];
		int f = g->flow[start][v];
			if(g->visited[v] && g->varr[start][v] > 0){
				if(f < cap){
					tmp = (flow < cap - f)? flow : cap - f;
					update = pushFlow(g, v, tmp);
					if(update > 0){
						g->flow[start][v] += update;
						g->flow[v][start] -= update;
						return update;
					}
				}	
		}
	}
	return 0;
}
