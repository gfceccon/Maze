#include "game.h"

#include <util/log.h>

Game::Game(int width, int height)
{
	cube = new Cube();
	camera = new Camera(width, height);

	program = glCreateProgram();

	vertex_shader = new	Shader("simple_vertex.glsl", GL_VERTEX_SHADER, program);
	frag_shader = new Shader("simple_fragment.glsl", GL_FRAGMENT_SHADER, program);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status)
	{
		GLchar info[512];
		glGetProgramInfoLog(program, 512, nullptr, info);
		Log::error(info);
	}

	cube->bind();
	camera->translate(0.0f, 0.0f, -3.0f);
}


Game::~Game()
{
	glDeleteProgram(program);
	delete vertex_shader;
	delete frag_shader;
	delete cube;
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
	glUseProgram(program);

	camera->bind(program, vertex_shader);

	glm::vec3 axis(0.0f, 1.0f, 1.0f);
	cube_transf = glm::rotate(cube_transf, glm::radians(20.0f * delta), axis);
	vertex_shader->setMat4(cube_transf, "transform");
	cube->draw();
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}