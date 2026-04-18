#pragma once
#include <SDL3/SDL.h>

class GameRenderer {
public:
	GameRenderer();
	~GameRenderer();
	void draw();
	void run();
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
