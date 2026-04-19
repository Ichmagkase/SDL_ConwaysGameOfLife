#pragma once
#include <SDL3/SDL.h>
#include "engine.h"

class GameRenderer {
public:
	GameRenderer();
	~GameRenderer();
	void draw(int width, int height, const std::vector<CellState>& game);
	void run(GoLEngine& engine);
private:
	void InitSDLCore();
	void InitSDLWindow();
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	int window_height;
	int window_width;
	int grid_size;
};
