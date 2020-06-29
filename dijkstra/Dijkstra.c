#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SIZE 100
#define NUMBER_OF_CHANGED_COLUMN 10
#define INFINITY 10000

int random(int max);

int main(void) {
	// Set the seed
	srand((unsigned)time(0));

	int network[SIZE][SIZE]; // Create an array to store the network
	int randomNumber, vertex, min, destinationVertex;
	int distance[SIZE], path[SIZE], flag[SIZE], result[SIZE][SIZE];

	// Initialize the network
	for (int row = 0; row < SIZE; row++)
			for (int column = 0; column < SIZE; column++)
				network[row][column] = 0;

	// Randomize the network
	for (int row = 0;row < SIZE; row++) {
		for (int column = 0; column < NUMBER_OF_CHANGED_COLUMN; column++) {
			while ((randomNumber = random(SIZE)) == row || network[row][randomNumber] != 0)
				randomNumber = random(SIZE);
			network[row][randomNumber] = network[randomNumber][row] = random(10) + 1;
		}
	}

	// Print the network
	for (int row = 0; row < SIZE; row++) {
		for (int column = 0; column < SIZE; column++)
			printf("%3d", network[row][column]);
		printf("\n");
	}

	printf("\n");

	// Set the 0 that is not on the diagonal to INFINITY
	for (int row = 0; row < SIZE; row++) {
		for (int column = 0; column < SIZE; column++) {
			if (row != column && network[row][column] == 0)
				network[row][column] = INFINITY;
		}
	}

	for (destinationVertex = 0; destinationVertex < SIZE; destinationVertex++) {
		for(int i = 0; i < SIZE; i++) {
			distance[i] = network[destinationVertex][i];
			if(i != destinationVertex && distance[i] < INFINITY)
				path[i] = destinationVertex;
			else
				path[i] = -1;
		}

		// Initialize the flag[SIZE]
		for (int i = 0; i < SIZE; i++)
			flag[i] = 0;
		flag[destinationVertex] = 1;

		while(1) {
			min = INFINITY;
			vertex = -1;
			for(int i = 0; i < SIZE; i++) {
				if(!flag[i]) {
					if(distance[i] < min) {
						min = distance[i];
						vertex = i;
					}
				}
			}

			if(vertex == -1) break;
			/* Flag does not change, representing that it has already been the shortest path
			*  for the destination vertex */

			flag[vertex] = 1; // Refresh the shortest way

			for(int i = 0; i < SIZE; i++) {
				if(!flag[i] && network[vertex][i] != INFINITY &&
						distance[vertex] + network[vertex][i] < distance[i]) {
					distance[i] = distance[vertex] + network[vertex][i];
					path[i]=vertex;
				}
			}
		}

		for (int row = 0; row < SIZE; row++)
			if (row == destinationVertex)
				result[row][destinationVertex] = row;
			else
				result[row][destinationVertex] = path[row];
	}

	// Print the shortest path
	for (int row = 0; row < SIZE; row++) {
		for (int column = 0; column < SIZE; column++)
			printf("%3d", result[row][column]);
		printf("\n");
	}

	return 0;
}

/* return a random number between 0 and max - 1 */
int random(int max) {
	return rand() % max;
}


