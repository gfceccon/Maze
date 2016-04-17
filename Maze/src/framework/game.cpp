#include "game.h"

#include <util/log.h>

Game::Game()
{
	square = new Square();

	program = glCreateProgram();

	vertex_shader = new	Shader("simple_vertex.glsl", GL_VERTEX_SHADER, program);
	frag_shader = new	Shader("simple_fragment.glsl", GL_FRAGMENT_SHADER, program);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status)
	{
		GLchar info[512];
		glGetProgramInfoLog(program, 512, nullptr, info);
		Log::error(info);
	}

	square->bind();
}


Game::~Game()
{
	glDeleteProgram(program);
	delete vertex_shader;
	delete frag_shader;
	delete square;
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
	glUseProgram(program);
	square->draw();
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}