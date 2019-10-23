// dinic.h
#ifndef DINIC_H
#define DINIC_H

#include "graph.h"

int dinic(struct Graph g);
int pushFlow(struct Graph *g, int start, int flow);

#endif