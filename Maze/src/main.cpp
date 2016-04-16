#include <framework\window.h>
#include <framework\game.h>

int main(void)
{ 
	Window* window = new Window("Maze", 800, 600);
	Game* game = new Game();
	game->setClearColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

	window->start(game);

	delete game;
	delete window;
}