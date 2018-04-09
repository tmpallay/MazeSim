#include "nav.c"


// Returns the next move direction
int determineMove(int x, int y) {

	int nextMove;
	int nextDistance;
	if (x > 0) {
		if (maze[x - 1][y][0] < maze[x][y][0] && (maze[x][y][1] & 8) == 0) {
			nextMove = 1;
			nextDistance = maze[x - 1][y][0];
		}
	}

	if (y < (sizey - 1)) {
		if (maze[x][y + 1][0] < maze[x][y][0] && (maze[x][y][1] & 4) == 0 && maze[x][y + 1][0] < nextDistance) {
			nextMove = 2;
			nextDistance = maze[x][y + 1][0];
		}
	}

	if (x < (sizex - 1)) {
		if (maze[x + 1][y][0] < maze[x][y][0] && (maze[x][y][1] & 2) == 0 && maze[x + 1][y][0] < nextDistance) {
			nextMove = 3;
			nextDistance = maze[x + 1][y][0];
		}
	}

	if (y > 0) {
		if (maze[x][y - 1][0] < maze[x][y][0] && (maze[x][y][1] & 1) == 0 && maze[x][y - 1][0] < nextDistance) {
			nextMove = 4;
		}
	}

	return nextMove;

}

// Returns the new current direction
int move(int nextMove, int currentDir, int* xpnt, int* ypnt) {

	switch(nextMove) {

		// Need to move towards negative x
		case 1:
			if (nextMove == currentDir) {
				// Move forward
			} else if (currentDir == 2) {
				// Turn left
				// Move forward
			} else if (currentDir == 3) {
				// Do 180
				// Move forward
			} else {
				// Turn right
				// Move forward
			}
			*xpnt -= 1;
			break;

		// Need to move towards positive y
		case 2:
			if (nextMove == currentDir) {
				// Move forward
			} else if (currentDir == 1) {
				// Turn right
				// Move forward
			} else if (currentDir == 3) {
				// Turn left
				// Move forward
			} else {
				// do 180
				// Move forward
			}
			*ypnt += 1;
			break;

		// Need to move towards positive x
		case 3:
			if (nextMove == currentDir) {
				// Move forward
			} else if (currentDir == 1) {
				// do 180
				// Move forward
			} else if (currentDir == 2) {
				// Turn right
				// Move forward
			} else {
				// turn left
				// Move forward
			}
			*xpnt += 1;
			break;

		// Need to move towards negative y
		case 4:
			if (nextMove == currentDir) {
				// Move forward
			} else if (currentDir == 1) {
				// Turn left
				// Move forward
			} else if (currentDir == 2) {
				// do 180
				// Move forward
			} else {
				// turn right
				// Move forward
			}
			*ypnt -= 1;
			break;

		return currentDir;

	}

}