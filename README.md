# MazeSim


For the array of wall values:

Wall to the North: 	0000 1000	-	8
			East: 	0000 0100	-	4
			South: 	0000 0010	-	2
			West: 	0000 0001	-	1


For Integer Directional Values:

Facing 	North:	1
		East:	2
		South:	3
		West:	4


maze[x][y][0] holds DISTANCE VALUES
maze[x][y][1] holds WALL VALUES


Modified Flood Fill Algorithm:

	Push the current cell to the stack

	while (stackIndex != -1) {
		If the current cell's distance value needs modified:
			modify its value
			push all neighbors to the stack
	}

