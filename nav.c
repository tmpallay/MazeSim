#include <stdio.h>
#include "methods.h"

int sizex = 6;
int sizey = 13;
extern unsigned char maze[6][13][2];

int main() {

	// Setting max distance
	int currentDistance = 8;
	int nextMove = 1;
	int currentDir = 1;
	int x = sizex - 1;
	int y = 0;
	int* xpnt = &x;
	int* ypnt = &y;

	for (int i = 0; i < sizex; i++) {
		for (int j = 0; j < sizey; j++) {
			maze[i][j][1] = 0;
		}
	}
	for (int j = 0; j < sizey; j++) {
		maze[0][j][1] = maze[0][j][1] | 8;
		maze[sizex - 1][j][1] = maze[sizex - 1][j][1] | 2;
	}
	for (int i = 0; i < sizex; i++) {
		maze[i][0][1] = maze[i][0][1] | 1;
		maze[i][sizey - 1][1] = maze[i][sizey - 1][1] | 4;
	}

	// Filling first z layer of maze with original distance values

	for (int i = 0; i < sizex; i++) {
		for (int j = 0; j < sizey; j++) {
			printf("%d ", maze[i][j][1]);
		}
	printf("\n");
	}

	while (currentDistance != 0) {
		
		// Record new walls
		// Modify the distance array
		nextMove = determineMove(x, y);
		currentDir = move(nextMove, currentDir, xpnt, ypnt);

	}

}