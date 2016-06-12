#include "framework/game/window.h"
#include "maze/game.h"
#include <iostream>

int main(int argc, char const *argv[]) {
	const int width = 1024, height = 576;
	Window* window = new Window("Maze", width, height);
	Game* game = nullptr;

	try {
		game = new Game(width, height);
	} catch (std::runtime_error e) {
		delete window;
		return -1;
	}

	window->setScene(game);
	window->start();

	delete game;
	delete window;

	return 0;
}
