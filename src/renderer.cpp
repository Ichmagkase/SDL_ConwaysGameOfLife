#include "renderer.h"
#include <thread>
#include <chrono>
#include <iostream>

GameRenderer::GameRenderer(GoLEngine &gol_engine) {
	window_width = 1920;
	window_height = 1080;
	engine = &gol_engine;
	rects.reserve(engine->game.size());
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
	cellWidth = static_cast<float>(window_width) / engine->matrix_width;
	cellHeight = static_cast<float>(window_height) / engine->matrix_height;
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, cellWidth, cellHeight);
}

void GameRenderer::run() {
	
	bool isRunning = true;
	SDL_Event event;


	while (isRunning) {
		auto frame_start = std::chrono::high_resolution_clock::now();
		draw();
		auto poll_start = std::chrono::high_resolution_clock::now();
		while (SDL_PollEvent(&event)) {

			//switch (event.type) {
			//	case SDL_EVENT_QUIT
			//}

			if (event.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}
		}
		auto engine_step_start = std::chrono::high_resolution_clock::now();
		engine->step();
		auto end_loop = std::chrono::high_resolution_clock::now();
		// SDL_Delay(10);

		auto draw_time = std::chrono::duration_cast<std::chrono::microseconds>(
			poll_start - frame_start
		);
		auto poll_event_time = std::chrono::duration_cast<std::chrono::microseconds>(
			engine_step_start - poll_start
		);
		auto step_time = std::chrono::duration_cast<std::chrono::microseconds>(
			end_loop - engine_step_start
		);

		std::cout << "Draw time: " << std::setw(6) << draw_time
			<< " | Poll event time: " << std::setw(6) << poll_event_time
			<< " | Simulation step time: " << std::setw(6) << step_time
			<< "\n";
	}

	SDL_Quit();
}

void GameRenderer::draw() {
	SDL_SetRenderDrawColor(renderer, 33, 33, 33, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	rects.clear();

	for (int y = 0; y < engine->matrix_height; y++) {
		for (int x = 0; x < engine->matrix_width; x++) {
			int index = y * engine->matrix_width + x;

			if (engine->game[index] == CellState::CELL_ALIVE) {
				rects.push_back({
					(float)x * cellWidth,
					(float)y * cellHeight,
					(float)cellWidth,
					(float)cellHeight
				});
			}
		}
	}
	SDL_RenderFillRects(renderer, rects.data(), rects.size());

	SDL_RenderPresent(renderer);
}