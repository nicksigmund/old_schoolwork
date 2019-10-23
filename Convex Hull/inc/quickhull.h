// quickhull.h

#ifndef QUICKHULL_H
#define QUICKHULL_H

#include "coord.h"


struct CoordArr quickhull(struct CoordArr arr);
void findHull(struct CoordArr arr, struct CoordArr *hull, struct Coord point1, struct Coord point2, int side);
void printHull(struct CoordArr arr);
struct CoordArr rmDuplicates(struct CoordArr arr);
void worstCaseHull();

#endif