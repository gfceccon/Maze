#include "framework/window.h"
#include "framework/game.h"
#include <iostream>

int main(int argc, char const *argv[]) {
	const int width = 800, height = 600;
	Window* window = new Window("Maze", width, height);
	Game* game = nullptr;
	try {
		game = new Game(width, height);
	} catch (const std::runtime_error& e) {
		delete window;
		return -1;
	}

	game->setClearColor(Color(0.2f, 0.3f, 0.3f, 1.0f));

	window->start(game);

	delete game;
	delete window;

	return 0;
}
