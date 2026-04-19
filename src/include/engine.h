#pragma once

#include <vector>

enum CellState {
	CELL_ALIVE,
	CELL_DEAD
};

class GoLEngine {
public:
	GoLEngine();
	~GoLEngine();
	void load_from_config(const char* start_data);
	void step();
	std::vector<CellState> game;
	std::vector<CellState> next_buffer;
	int matrix_width;
	int matrix_height;
private:
	int count_alive_neighbors(int x, int y);
	int is_alive(int x, int y);
};