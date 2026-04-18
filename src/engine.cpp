#include "engine.h"
#include <vector>

GoLEngine::GoLEngine() {
	matrix_width = 500;
	matrix_height = 500;
	const int matrix_size = matrix_width * matrix_height;

	game = std::vector<int>(matrix_size, 0);
}

void GoLEngine::step() {
	for (int y = 0; y < matrix_height; y++) {
		for (int x = 0; x < matrix_width; x++) {
			int index = y * matrix_width + x;

			int alive_neighbors = count_alive_neighbors(x, y);
			if (alive_neighbors < 2 || alive_neighbors > 3) {
				// cell dies
			}
			else if (alive_neighbors == 3) {
				// if cell (x, y) is dead: come alive
				// else: survive
			}
			else if (alive_neighbors == 2) {
				// if cell (x, y) is alive or new: survive
				// else: stay dead
			}
		}
	}
}

int GoLEngine::count_alive_neighbors(int x, int y) {

}