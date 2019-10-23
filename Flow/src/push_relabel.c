#include "../inc/push_relabel.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int pushRelabel(struct Graph g){
	preflow(&g);
	int tmp = overFlow(&g);
	int q, r = 0;
	do{
		if(push(&g, tmp) == 0){
			q = relabel(&g, tmp);
		}
		tmp = overFlow(&g);
	}while(tmp > 0);

	

	return g.excess[g.n-1];
}

int overFlow(struct Graph *g){
	for(int i = 1; i < g->n - 1; i++){
		if(g->excess[i] > 0){
			return i;
		}
	}

	return -1;
}
int push(struct Graph *g, int n){
	int update, cap, flow, excess;
	for(int i = 0; i < g->n; i++){
		if(g->varr[n][i] > 0){
			if(g->flow[n][i] == g->varr[n][i]){
				continue;
			}
			if(g->height[n] > g->height[i]){
				cap = g->varr[n][i];
				flow = g->flow[n][i];
				excess = g->excess[n];
				update = (cap - flow < excess) ? (cap - flow) : excess;
				
				g->excess[n] -= update;
				g->excess[i] += update;

				g->flow[n][i] -= update;
				g->flow[i][n] += update;
				return 1;
			}
		}
	}
	return 0;
}
int relabel(struct Graph *g, int n){
	int i = 0;
	int min = INT_MAX;
	for(i; i < g->n; i ++){
		if(g->flow[n][i] > 0){
			if(g->flow[n][i] == g->varr[n][i]){
				continue;
			}
			if(g->height[i] <= min){
				min = g->height[i];
				g->height[n] = min + 1;
			}
		}
	}
	if(i == g->n){
		return g->excess[g->n - 1];
	}
	return 0;
}

void preflow(struct Graph *g){
	for(int i = 0; i < g->n; i++){
		if(g->varr[0][i] > 0){
			g->flow[0][i] = -g->varr[0][i];
			g->excess[i] = g->varr[0][i];
			g->flow[i][0] = g->varr[0][i];
		}
	}
}