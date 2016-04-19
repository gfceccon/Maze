#include <framework\window.h>
#include <framework\game.h>

int main(void)
{ 
	const int width = 800, height = 600;
	Window* window = new Window("Maze", width, height);
	Game* game = new Game(width, height);
	game->SetClearColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

	window->Start(game);

	delete game;
	delete window;
}