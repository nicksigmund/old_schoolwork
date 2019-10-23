// push_relabel.h

#ifndef PUSH_RELABEL_H
#define PUSH_RELABEL_H

#include "graph.h"

int pushRelabel(struct Graph g);
int push(struct Graph *g, int n);
int relabel(struct Graph *g, int n);
void preflow(struct Graph *g);
int overFlow(struct Graph *g);

#endif