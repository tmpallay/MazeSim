#include <stdio.h>

typedef struct {
	unsigned char x;
	unsigned char y;
} CELL;

unsigned char sizex = 6;
unsigned char sizey = 13;
// Array that holds wall and distance values
unsigned char maze[6][13][2];

int determineMove(unsigned char x, unsigned char y);
int move(int nextMove, int currentDir, unsigned char* xpnt, unsigned char* ypnt);
void ModifiedFloodFill(unsigned char x, unsigned char y);

int main() {

	int nextMove = 1;
	int currentDir = 1;
	unsigned char x = sizex - 1;
	unsigned char y = sizey - 1;
	unsigned char* xpnt = &x;
	unsigned char* ypnt = &y;

	printf("Initial x: %d\n", *xpnt);

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

	
	// !!!!!!FOR SIZEX = 6 AND SIZEY = 13!!!!!!
	unsigned char disMaze[6][13] = {{8,7,6,5,4,3,2,3,4,5,6,7,8},
									{7,6,5,4,3,2,1,2,3,4,5,6,7},
									{6,5,4,3,2,1,0,1,2,3,4,5,6},
									{6,5,4,3,2,1,0,1,2,3,4,5,6},
									{7,6,5,4,3,2,1,2,3,4,5,6,7},
									{8,7,6,5,4,3,2,3,4,5,6,7,8}};
	/*maze[2][6][0] = 0;
	maze[3][6][0] = 0;
	int done = 0;
	while(!done) {
		for (int i = 0; i < sizex; i++) {
			for (int j = 0; j < sizey; j++) {
				if (maze[i][j][0] != -1) {
					
				}
			}
		}
	}*/
	// Filling first z layer of maze with original distance values
	for (int i = 0; i < sizex; i++) {
		for (int j = 0; j < sizey; j++) {
			maze[i][j][0] = disMaze[i][j];
		}
	}

	// Printing the initial wall values
	printf("Initial Wall Values\n");
	for (int i = 0; i < sizex; i++) {
		for (int j = 0; j < sizey; j++) {
			printf("%d ", maze[i][j][1]);
		}
	printf("\n\n");
	}

	// Printing the initial distance values
	printf("Initial Distance Values\n");
	for (int i = 0; i < sizex; i++) {
		for (int j = 0; j < sizey; j++) {
			printf("%d ", maze[i][j][0]);
		}
	printf("\n\n");
	}


	unsigned char TESTMAZE[6][13] = {	{15, 9, 10, 10, 10, 10, 10, 10, 10, 10, 8, 10, 14},
										{9, 2, 12, 9, 10, 10, 10, 8, 8, 12, 1, 10, 12},
										{5, 13, 5, 3, 10, 12, 13, 5, 7, 7, 5, 15, 5},
										{1, 4, 5, 9, 12, 5, 3, 4, 9, 10, 2, 10, 6},
										{5, 5, 7, 5, 5, 5, 13, 5, 5, 9, 8, 10, 14},
										{7, 3, 10, 6, 3, 2, 6, 7, 3, 6, 3, 10, 14}
									};

	// Maze-Solving Loop
	while (maze[x][y][0] != 0) {
		
		// Record new walls
		//printf("\nAttempting to record walls...\n");
		maze[x][y][1] = TESTMAZE[x][y];

		// Modify the distance array
		//printf("\nAttempting to flood fill...\n");
		ModifiedFloodFill(x, y);

		// Determine next move
		//printf("\nDetermining next move...\n");
		nextMove = determineMove(x, y);

		// Move to next position
		//printf("\nAttempting to move...\n");
		currentDir = move(nextMove, currentDir, xpnt, ypnt);
		//printf("--MOVE COMPLETED--\n\n\n");
		printf("My Current Position: %d, %d\n\n", x, y);

	}

	return 0;

}

// Modifies the Distance Array
void ModifiedFloodFill(unsigned char x, unsigned char y) {

	//printf("Flood Fill algorithm has been entered with x: %d y: %d\n", x, y);

	// Stack for Modified Flood Fill
	CELL stack[sizex * sizey];
	//printf("Stack has been created!\n");
	int stackIndex = 0;

	// Variable will hold the smallest distance value of all neighboring cells
	unsigned char disVal = 0;

	stack[0].x = x;
	stack[0].y = y;
	//printf("First cell has been pushed to stack\n");

	unsigned char xplaceholder;
	unsigned char yplaceholder;
	
	while (stackIndex != -1) {
		//printf("Stack index: %d\n", stackIndex);
		//printf("For current stack index x: %d y: %d\n", stack[stackIndex].x, stack[stackIndex].y);

		int directionOfLeastDistance = determineMove(stack[stackIndex].x, stack[stackIndex].y);
		//printf("Call to determineMove succeeded with move to: %d\n", directionOfLeastDistance);
		switch (directionOfLeastDistance) {
			case 1:
				disVal = maze[stack[stackIndex].x - 1][stack[stackIndex].y][0];
				//printf("disVal = %d\n", disVal);
				break;
			case 2:
				disVal = maze[stack[stackIndex].x][stack[stackIndex].y + 1][0];
				//printf("disVal = %d\n", disVal);
				break;
			case 3:
				disVal = maze[stack[stackIndex].x + 1][stack[stackIndex].y][0];
				//printf("disVal = %d\n", disVal);
				break;
			case 4:
				disVal = maze[stack[stackIndex].x][stack[stackIndex].y - 1][0];
				//printf("disVal = %d\n", disVal);
				break;
		}
		//printf("Distance value obtained\n");

		//printf("The distance Value in the current cell: %d\n", maze[x][y][0]);
		//printf("disVal: %d\n", disVal);
		if (maze[stack[stackIndex].x][stack[stackIndex].y][0] != (disVal + 1)) {
			//printf("DisVal check performed and WE NEED TO MAKE CHANGES\n");

			// Current cell's distance value = 1 + smallest distance value of neighbor
			maze[stack[stackIndex].x][stack[stackIndex].y][0] = disVal + 1;
				
				/* UPDATED DISTANCE ARRAY
				printf("UPDATED DISTANCE ARRAY\n");
				
				for (int i = 0; i < sizex; i++) {
					for (int j = 0; j < sizey; j++) {
						printf("%d ", maze[i][j][0]);
					}
					printf("\n\n");
				}
				UPDATED DISTANCE ARRAY */

			xplaceholder = stack[stackIndex].x;
			yplaceholder = stack[stackIndex].y;
			//printf("Placeholder Values assigned x: %d y: %d\n", xplaceholder, yplaceholder);

			if ((xplaceholder > 0) && ((maze[xplaceholder][yplaceholder][1] & 8) == 0)) {
				stackIndex++;
				//printf("Attempting to push cell to North to stack at index %d\n", stackIndex);
				stack[stackIndex].x = xplaceholder - 1;
				stack[stackIndex].y = yplaceholder;
				//printf("Cell to the North pushed to stack\n");
			}
			if ((yplaceholder < sizey - 1) && ((maze[xplaceholder][yplaceholder][1] & 4) == 0)) {
				stackIndex++;
				//printf("Attempting to push cell to East to stack at index %d\n", stackIndex);
				stack[stackIndex].x = xplaceholder;
				stack[stackIndex].y = yplaceholder + 1;
				//printf("Cell to the East pushed to stack\n");
			}
			if ((xplaceholder < sizex - 1) && ((maze[xplaceholder][yplaceholder][1] & 2) == 0)) {
				stackIndex++;
				//printf("Attempting to push cell to South to stack at index %d\n", stackIndex);
				stack[stackIndex].x = xplaceholder + 1;
				stack[stackIndex].y = yplaceholder;
				//printf("Cell to the South pushed to stack\n");
			}
			if ((yplaceholder > 0) && ((maze[xplaceholder][yplaceholder][1] & 1) == 0)) {
				stackIndex++;
				//printf("Attempting to push cell to West to stack at index %d\n", stackIndex);
				stack[stackIndex].x = xplaceholder;
				stack[stackIndex].y = yplaceholder - 1;
				//printf("Cell to the West pushed to stack\n");
			}
		} else {
			stack[stackIndex].x = 0;
			stack[stackIndex].y = 0;
			stackIndex--;
		}

	}

//printf("\n***********Flood Fill Call has completed*********\n\n");
/*printf("New Distance Values\n");
	for (int i = 0; i < sizex; i++) {
		for (int j = 0; j < sizey; j++) {
			printf("%d ", maze[i][j][0]);
		}
	printf("\n\n");
	}*/
}

// Returns the next move direction
int determineMove(unsigned char x, unsigned char y) {

	//printf("CALL TO DETERMINEMOVE MADE WITH x: %d y: %d\n", x, y);
	unsigned char nextMove = 0;
	unsigned char nextDistance = 232;
	if (x > 0) {
		//printf("distance value to the north: %d\n", maze[x-1][y][0]);
		//printf("current distance value: %d\n", maze[x][y][0]);
		//printf("wall values of current cell: %d\n", maze[x][y][1]);

		//if ((maze[x - 1][y][0] < maze[x][y][0]) && ((maze[x][y][1] & 8) == 0)) {
		
		if ((maze[x - 1][y][0] <= nextDistance) && ((maze[x][y][1] & 8) == 0)) {
			//printf("determineMove: move to North is available\n");
			nextMove = 1;
			nextDistance = maze[x - 1][y][0];
		}
	}

	if (y < (sizey - 1)) {
		//printf("distance value to the east: %d\n", maze[x][y+1][0]);
		//printf("current distance value: %d\n", maze[x][y][0]);
		//printf("wall values of current cell: %d\n", maze[x][y][1]);
		if ((maze[x][y + 1][0] <= nextDistance) && ((maze[x][y][1] & 4) == 0) && (maze[x][y + 1][0] <= nextDistance)) {
			//printf("determineMove: move to East is available\n");
			nextMove = 2;
			nextDistance = maze[x][y + 1][0];
		}
	}

	if (x < (sizex - 1)) {
		//printf("distance value to the south: %d\n", maze[x+1][y][0]);
		//printf("current distance value: %d\n", maze[x][y][0]);
		//printf("wall values of current cell: %d\n", maze[x][y][1]);
		if ((maze[x + 1][y][0] <= nextDistance) && ((maze[x][y][1] & 2) == 0) && (maze[x + 1][y][0] <= nextDistance)) {
			//printf("determineMove: move to South is available\n");
			nextMove = 3;
			nextDistance = maze[x + 1][y][0];
		}
	}

	if (y > 0) {
		//printf("distance value to the west: %d\n", maze[x][y-1][0]);
		//printf("current distance value: %d\n", maze[x][y][0]);
		//printf("wall values of current cell: %d\n", maze[x][y][1]);
		if ((maze[x][y - 1][0] <= nextDistance) && ((maze[x][y][1] & 1) == 0) && (maze[x][y - 1][0] <= nextDistance)) {
			//printf("determineMove: move to West is available\n");
			nextMove = 4;
		}
	}

	//printf("CALL TO DETERMINEMOVE RETURNING A VALUE OF %d\n", nextMove);
	return nextMove;

}

// Returns the new current direction
int move(int nextMove, int currentDir, unsigned char* xpnt, unsigned char* ypnt) {

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
			*xpnt = *xpnt - 1;
			printf("Moved North\n\n");
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
			*ypnt = *ypnt + 1;
			printf("Moved East\n\n");
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
			*xpnt = *xpnt + 1;
			printf("Moved South\n\n");
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
			*ypnt = *ypnt - 1;
			printf("Moved West\n\n");
			break;

		default:
			printf("INVALID MOVE");

	}

	return nextMove;

}