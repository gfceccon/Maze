#include "framework/game/window.h"
#include "maze/game_scene.h"
#include "test.h"
#include <iostream>

int main(int argc, char const *argv[]) {
	Window::width = 1024;
	Window::height = 576;
	
	Window window = Window("Maze");

	//Game* game = nullptr;
	Test* test = nullptr;

	try {
		//game = new Game();
		test = new Test();
	} catch (std::runtime_error e) {
		return EXIT_FAILURE;
	}

	//window.setScene(game);
	window.setScene(test);
	window.start();

	return EXIT_SUCCESS;
}
