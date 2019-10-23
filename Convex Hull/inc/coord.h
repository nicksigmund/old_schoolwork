// coord.h

#ifndef COORD_H
#define	COORD_H

struct Coord {
	int x;
	int y;
	int null;		// flag used to in rmDuplicates to remove duplicate coordinates from quickhull
};

struct CoordArr{
	int n;		// number of elements
	int m;		// max number of elements
	struct Coord* coords;
};

// Calculates the angle orientation of angle p1p2p3
int orientation(struct Coord p1, struct Coord p2, struct Coord p3);
// inserts a Coord struct into an array of Coords
void insertCoord(struct CoordArr *arr, struct Coord p);
// randomly generates a coordinate
struct Coord randomCoord();
// calls randomcCoord() n times to fill an array
struct CoordArr randomCoordArr(int n);
// fills a CoordArr with input from a file
struct CoordArr fileCoords(const char* fname);
// prints a single Coord to the console
void printCoord(struct Coord p);
// prints the contents of a CoordArr to the console
void printCoordArr(struct CoordArr arr);
// turns cpy into a duplicate of arr
void copyCoordArr(struct CoordArr arr, struct CoordArr *cpy);
// allows CoordArr to act like a stack
struct Coord pop(struct CoordArr *arr);
// compares the counter-clockwise-ness of two angles in reference to ref
int coordCmp(struct Coord a, struct Coord b, struct Coord ref);
void coordSwap(struct CoordArr *arr, int a, int b);
// returns the distance beetween two Coords
double coordDistance(struct Coord a, struct Coord b);
// returns 1 if the coords contain the same x and y values
int sameCoord(struct Coord a, struct Coord b);
// finds the lowest value x coord (and y coord if there is a tie)
// and moves it to index 0;
void bottomPointToZero(struct CoordArr *arr);


#endif

