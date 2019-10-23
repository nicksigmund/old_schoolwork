// queue.c

#include "../inc/queue.h"
#include <stdlib.h>

void enQ (struct Q *q, int v){
	q->vlist[q->tail] = v;
	q->tail = (q->tail + 1) % q->n;
}

int deQ(struct Q *q){
	int v = q->vlist[q->head];
	q->head = (q->head + 1) % q->n;
	return v;
}

void initQ(struct Q *q, int n){
	q->vlist = malloc(sizeof(int) * n);
	q->head = 0;
	q->tail= 0;
	q->n = n;
}

void freeQ(struct Q *q){
	free(q->vlist);
}