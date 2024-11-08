#include <iostream>
#include <chrono>
#include <thread>


// Rules (Conway's Game of Life)		
/*
1) Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2) Any live cell with two or three live neighbours lives on to the next generation.
3) Any live cell with more than three live neighbours dies, as if by overpopulation.
4) Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
*/

static const char LIVE = (unsigned char)219;		   // █
static const char DEAD = (unsigned char)176;		   // ░
static const int GRID_SIZE = 30;
static const int WAIT_TIME = 100;

bool gameGrid[GRID_SIZE][GRID_SIZE] = {};
bool tempGrid[GRID_SIZE][GRID_SIZE] = {};
int generation = 0;

void InitialiseGrid();
void DrawGrid();
void CalculateGrid();

int main() {
	InitialiseGrid();
	while (1) {
		DrawGrid();
		CalculateGrid();
		// Sleep to see each generation clearly
		std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));
		generation++;
	}
}

// The initial grid generation
void InitialiseGrid() {
	srand(time(NULL));
	for (int y = 0; y < GRID_SIZE; y++) {
		for (int x = 0; x < GRID_SIZE; x++) {
			// 70% chance of gridplot being alive
			gameGrid[y][x] = rand() % 100 > 70;
		}
	}
}

void DrawGrid() {
	// Set cursor to top left
	std::cout << "\033[H";
	// Apply ASCII depending on true/false
	for (int y = 0; y < GRID_SIZE; y++) {
		for (int x = 0; x < GRID_SIZE; x++) {
			if (gameGrid[y][x]) {
				std::cout << LIVE << LIVE;
			}
			else {
				std::cout << DEAD << DEAD;
			}
		}
		// For Next row
		std::cout << '\n';
	}
	// Print out current generation
	std::cout << '\n' << "Generation: " << generation;
}

void CalculateGrid() {
	// Loop through each point in grid
	for (int y = 0; y < GRID_SIZE; y++) {
		for (int x = 0; x < GRID_SIZE; x++) {
			// Neighbour counter
			int n = 0;
			// Loop through neighbours
			for (int nY = -1; nY <= 1; nY++) {
				for (int nX = -1; nX <= 1; nX++) {
					// Discount Self
					if (nY == 0 && nX == 0) {
						continue;
					}
					// Add Live Neighbour
					int ny = y + nY, nx = x + nX;
					if (ny >= 0 && ny < GRID_SIZE && nx >= 0 && nx < GRID_SIZE) {
						n += gameGrid[ny][nx];

					}
				}
			}
			// Apply Game Rules to temp grid
			if (gameGrid[y][x]) {
				tempGrid[y][x] = (n == 2 || n == 3);
			}
			else {
				tempGrid[y][x] = (n == 3);
			}
		}
	}

	// Apply tempgrid to next generation
	for (int y = 0; y < GRID_SIZE; y++) {
		for (int x = 0; x < GRID_SIZE; x++) {
			gameGrid[y][x] = tempGrid[y][x];
		}
	}
}