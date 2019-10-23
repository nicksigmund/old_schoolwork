// queue.h
#ifndef QUEUE_H
#define QUEUE_H


struct Q{
	int n;
	int head;
	int tail;
	int* vlist;
};

void enQ (struct Q *q, int v);
int deQ(struct Q *q);
void initQ(struct Q *q, int n);
void freeQ(struct Q *q);

#endif