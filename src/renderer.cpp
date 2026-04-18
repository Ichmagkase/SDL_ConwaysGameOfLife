#include "renderer.h"

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

void GameRenderer::run() {
	bool isRunning = true;
	SDL_Event event;

	while (isRunning) {
		draw();
		while (SDL_PollEvent(&event)) {

			//switch (event.type) {
			//	case SDL_EVENT_QUIT
			//}

			if (event.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}
		}
	}

	SDL_Quit();
}

void GameRenderer::draw() {
	SDL_SetRenderDrawColor(renderer, 33, 33, 33, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}