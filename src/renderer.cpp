#include "renderer.h"
#include <thread>
#include <chrono>

GameRenderer::GameRenderer() {
	window_height = 500;
	window_width = 500;
	InitSDLCore();
	InitSDLWindow();
}

GameRenderer::~GameRenderer() {
	SDL_Log("Destroyed");
}

void GameRenderer::InitSDLCore() {
	SDL_SetAppMetadata("SDL_GoL", "0.1.0", "com.zackerydrake.GoL");
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
}

void GameRenderer::InitSDLWindow() {
	SDL_CreateWindowAndRenderer("AudioVis", window_width, window_height, SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_SetRenderLogicalPresentation(renderer, window_width, window_height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	SDL_SetRenderVSync(renderer, 1);
}

void GameRenderer::run(GoLEngine &engine) {
	
	bool isRunning = true;
	SDL_Event event;

	while (isRunning) {
		draw(engine.matrix_width, engine.matrix_height, engine.game);
		while (SDL_PollEvent(&event)) {

			//switch (event.type) {
			//	case SDL_EVENT_QUIT
			//}

			if (event.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}
		}
		engine.step();
		SDL_Delay(10);
	}

	SDL_Quit();
}

void GameRenderer::draw(int width, int height, const std::vector<CellState>& game) {
	SDL_SetRenderDrawColor(renderer, 33, 33, 33, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	// Keep these as floats
	float cellWidth = static_cast<float>(window_width) / width;
	float cellHeight = static_cast<float>(window_height) / height;
	 
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// FIX: GEMINI GENERATED/MODIFIED
			int index = y * width + x;

			if (game[index] == CellState::CELL_ALIVE) {
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

				// Use SDL_FRect instead of SDL_Rect for SDL3
				SDL_FRect cellRect;
				cellRect.x = x * cellWidth;
				cellRect.y = y * cellHeight;
				cellRect.w = cellWidth;
				cellRect.h = cellHeight;

				SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, cellWidth, cellHeight);
				


				SDL_RenderFillRect(renderer, &cellRect);
			}
		}
	}

	SDL_RenderPresent(renderer);
}