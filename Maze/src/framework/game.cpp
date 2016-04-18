#include "game.h"

#include <util/log.h>

Game::Game(int width, int height)
{
	maze = new Maze("maze.bmp");
	camera = new Camera(width, height);
	program = new Program();

	program->addShader("simple_vertex.glsl", GL_VERTEX_SHADER)
		->addShader("simple_fragment.glsl", GL_FRAGMENT_SHADER);
	program->link();

	camera->translate(-10.5f, -10.5f, -25.0f);
}


Game::~Game()
{
	delete program;
	delete maze;
	delete camera;
}


void Game::setClearColor(Color& color)
{
	this->clear = color;
	glClearColor(clear.r, clear.g, clear.b, clear.a);
}



void Game::update(float delta)
{

}

void Game::draw(float delta)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program->use();

	camera->bind(program);

	maze->draw(program);
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}