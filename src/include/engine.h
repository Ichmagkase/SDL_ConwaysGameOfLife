#pragma once

#include <vector>

class GoLEngine {
public:
	GoLEngine();
	~GoLEngine();
	void load_from_config();
	void step();
	std::vector<int> game;
	int matrix_width;
	int matrix_height;
private:
	int count_alive_neighbors(int x, int y);
};