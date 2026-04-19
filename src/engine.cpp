#include "engine.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

GoLEngine::GoLEngine() {
	matrix_width = 1000;
	matrix_height = 1000;
	const int matrix_size = matrix_width * matrix_height;
	
	game = std::vector<CellState>(matrix_size, CELL_DEAD);
} 

GoLEngine::~GoLEngine() {}

void GoLEngine::step() {
	next_buffer.assign(matrix_width * matrix_height, CELL_DEAD);
	for (int y = 0; y < matrix_height; y++) {
		for (int x = 0; x < matrix_width; x++) {
			int index = y * matrix_width + x;
			int alive_neighbors = count_alive_neighbors(x, y);
			if (alive_neighbors < 2 || alive_neighbors > 3) {
				next_buffer[index] = CELL_DEAD;
			}
			else if (alive_neighbors == 3) {
				if (game[index] == CELL_DEAD) {
					next_buffer[index] = CELL_ALIVE;
				}
				else {
					next_buffer[index] = CELL_ALIVE;
				}
			}
			else if (alive_neighbors == 2) {
				if (game[index] == CELL_ALIVE) {
					next_buffer[index] = CELL_ALIVE;
				}
				else {
					next_buffer[index] = CELL_DEAD;
				}
			}
		}
	}
	game = next_buffer;
}

int GoLEngine::count_alive_neighbors(int x, int y) {
	int alive_neighbors = 0;
	for (int dy = -1; dy < 2; dy++) {
		for (int dx = -1; dx < 2; dx++) {
			if (dx == 0 && dy == 0) 
				continue;
			alive_neighbors += is_alive(x + dx, y + dy);
		}
	}
	return alive_neighbors;
}

int GoLEngine::is_alive(int x, int y) {
	if (x < 0 || x >= matrix_width)
		return 0;
	if (y < 0 || y >= matrix_height)
		return 0;

	int index = y * matrix_width + x;

	return game[index] == CELL_ALIVE ? 1 : 0;
}

void GoLEngine::load_from_config(const char *config_file) {
	std::ifstream start_data(config_file);

	std::string line_buffer;
	std::getline(start_data, line_buffer);
	std::istringstream iss(line_buffer);
	int init_w, init_h;
	iss >> init_w >> init_h;

	int start_row = (matrix_height / 2) - (init_h / 2);
	int start_col = (matrix_width / 2) - (init_w / 2);

	for (int row = start_row; row < start_row + init_h; ++row) {
		// FIX: GEMINI GENERATED/MODIFIED:
		std::string line;

		// std::getline reads the line and automatically discards the '\n'
		if (std::getline(start_data, line)) {

			int index = (row * matrix_width) + start_col;

			// Safety first: Ensure we don't try to copy more characters 
			// than the line actually contains, preventing buffer over-reads.
			size_t copy_len = std::min(static_cast<size_t>(init_w), line.length());

			// std::transform applies a function (the lambda) to each character 
			// before placing it into the game vector.
			std::transform(line.begin(), line.begin() + copy_len, game.begin() + index,
				[](char c) {
					// IMPORTANT: Change '1' to whatever character your file uses 
					// to represent an alive cell (for example, '*' or 'O').
					return (c == 'x') ? CellState::CELL_ALIVE : CellState::CELL_DEAD;
				}
			);

			// In your C code, strcspn replaced the newline with a space. 
			// Because std::getline just drops the newline entirely, if your board 
			// logic relies on padding missing characters with spaces up to init_w, 
			// you handle it explicitly like this:
			for (size_t i = copy_len; i < init_w; ++i) {
				game[index + i] = CELL_DEAD;
			}
		}
	}
}