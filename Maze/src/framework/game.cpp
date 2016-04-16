#include "game.h"



Game::Game()
{
}


Game::~Game()
{
}


void Game::setClearColor(Color& color)
{
	this->clear = color;
	glClearColor(clear.r, clear.g, clear.b, clear.a);
}



void Game::update()
{

}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}