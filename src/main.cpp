#include <print>
#include "renderer.h"
#include "engine.h"
#include <iostream>

int main() {
	GoLEngine engine;
	GameRenderer renderer;
	engine.load_from_config("infile.txt");

	renderer.run(engine);
}
