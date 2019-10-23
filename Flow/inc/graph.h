// graph.h

#ifndef GRAPH_H
#define GRAPH_H

struct Graph{
	int n;	
	int **varr;
	int **flow;
	//int **r_flow;
	int *visited;
	int *height;
	int *excess;
};

struct Graph *loadGraph(const char *fname);
void initGraph(struct Graph *g, int n);
void printGraph(struct Graph g);
int BFS(struct Graph *g, int *path);
void freeGraph(struct Graph *g);




#endif