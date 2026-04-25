#pragma once
#include <SDL3/SDL.h>
#include "engine.h"

class GameRenderer {
public:
	GameRenderer(GoLEngine &engine);
	~GameRenderer();
	void draw();
	void run();
private:
	void InitSDLCore();
	void InitSDLWindow();
	SDL_Window* window;
	SDL_Renderer* renderer;
	GoLEngine *engine;
	SDL_Texture* texture;
	float cellWidth;
	float cellHeight;
	std::vector<SDL_FRect> rects;
public:
	int window_height;
	int window_width;
	int grid_size;
};
