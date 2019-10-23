// Graph.c

#include "../inc/graph.h"
#include "../inc/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Graph *loadGraph(const char* fname){
	//puts("loading graph...");
	FILE *in = fopen(fname, "r");
	
	int n = 0;
	int m = 0;
	char* buff;
	size_t r = 0;
	char str[50];
	int c = 0;
	int name, w, v;
	while(getline(&buff, &r, in) >= 0){
		m++;
	}
	//printf("m = %d\n",m);
	struct Graph *g = malloc(sizeof(struct Graph));
	initGraph(g, m);
	
	fseek(in, 0, SEEK_SET);
	while(getline(&buff, &r, in) >= 0){
		sscanf(buff, "%d%n",&name, &c);
		buff += c;
		while(sscanf(buff, "%d%*c%d%n", &v, &w, &c) > 0){
			buff += c;
			g->varr[name][v] = w;
		}
	}
	//printGraph(g);
	//fclose(in);

	return g;
}

void initGraph(struct Graph *g,int n){
	g->n = n;
	g->varr = calloc(n, sizeof(int *));
	g->flow = calloc(n, sizeof(int *));
	//g->r_flow = calloc(n, sizeof(int *));
	for(int i = 0; i < n; i++){
		g->varr[i] = calloc(n, sizeof(int));
		g->flow[i] = calloc(n, sizeof(int));
		//g->r_flow[i] = calloc(n, sizeof(int));
	}
	g->visited = calloc(n, sizeof(int));
	g->height = calloc(n, sizeof(int));
	g->height[0] = n;
	g->excess = calloc(n, sizeof(int));

}

void printGraph(struct Graph g){
	for (int i = 0; i < g.n; i++){
		for (int j = 0; j < g.n; j++){
			printf("%d ",g.flow[i][j]);
		}
		puts("");
	}
}

int BFS(struct Graph *g, int *path){
	struct Q q;
	initQ(&q, g->n);
	memset(g->visited, 0, sizeof(int) * g->n);

	enQ(&q, 0);
	g->visited[0] = 1;

	while(q.head != q.tail){
		int u = deQ(&q);
		//printf("breadth on %d\n", u);
		for(int v = 0; v < g->n; v++){
			if(g->visited[v] == 0 && g->flow[u][v] < g->varr[u][v]){
				enQ(&q, v);
				path[v] = u;
				g->visited[v] = 1;
				//printf("visited %d\n", v);
			}
		}
	}
	//printf("BFS result: %d\n", g.visited[g.n - 1]);
	return g->visited[g->n - 1];
}



void freeGraph(struct Graph* g){
	/*for(int i = 0; i < g->n; i++)
		free(g->varr[i]);
	free(g->varr);*/
}
