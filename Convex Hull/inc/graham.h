// graham.h

#ifndef GRAHAM_H
#define GRAHAM_H

#include "coord.h"

int pivot(struct CoordArr *arr, int l, int r, struct Coord ref);
void quicksort(struct CoordArr *arr, int l, int r, struct Coord ref);
struct CoordArr graham(struct CoordArr arr);

#endif