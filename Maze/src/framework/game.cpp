#include "game.h"
#include <iostream>
#include "../util/log.h"

std::queue<Event*> Game::events;
bool Game::key_states[1024];
Event* Game::last_mouse = nullptr;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	} else if (key != GLFW_KEY_UNKNOWN) {
		Game::key_states[key] = action != GLFW_RELEASE;
	}
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	Game::events.push(new Event(xpos, ypos));
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Game::events.push(new Event(xoffset, yoffset, true));
}

Game::Game(int width, int height)
{
	try {
		program = new Program();

		program->addShader("tex_vertex.glsl", GL_VERTEX_SHADER)
			->addShader("tex_fragment.glsl", GL_FRAGMENT_SHADER);
		program->link();
		maze = new Maze("maze.bmp");
		maze->init(program);

		pp_program = new Program();

		pp_program->addShader("screen_vertex.glsl", GL_VERTEX_SHADER)
			->addShader("inverse_fragment.glsl", GL_FRAGMENT_SHADER);
		pp_program->link();

		pp = new PostProcess(width, height, pp_program);

	} catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		throw;
	}

	player = new Player(maze->getEntryPosition());
	camera = new Camera(width, height);
}

Game::~Game()
{
	if (last_mouse)
		delete last_mouse;
	delete program;
	delete pp_program;
	delete pp;
	delete maze;
	delete camera;
}


void Game::setClearColor(const Color& color)
{
	this->clear = color;
	glClearColor(clear.r, clear.g, clear.b, clear.a);
}



void Game::update(float delta)
{
	if (Game::key_states[GLFW_KEY_D]){
		player->move(maze, Axis::X, delta * move_sensibility);
	}

	if (Game::key_states[GLFW_KEY_A]){
		player->move(maze, Axis::X, delta * -move_sensibility);
	}

	if (Game::key_states[GLFW_KEY_W]){
		player->move(maze, Axis::Z, delta * move_sensibility);
	}

	if (Game::key_states[GLFW_KEY_S]){
		player->move(maze, Axis::Z, delta * -move_sensibility);
	}

	while (events.size() > 0) {
		Event* e = events.front();
		events.pop();
		if (e->type == EventType::MOUSE) {
			if (last_mouse == nullptr) {
				last_mouse = e;
				continue;
			}
			float deltaX = static_cast<float>(e->x - last_mouse->x);
			float deltaY = static_cast<float>(last_mouse->y - e->y);

			camera->addEuler(delta * deltaY * rotation_sensibility, delta * deltaX * rotation_sensibility, 0.0f);

			delete last_mouse;
			last_mouse = e;
		} else if (e->type == EventType::SCROLL) {
			if(e->y < 0.0f) {
				camera->zoom(2.0f - zoom_sensibility);
			} else {
				camera->zoom(zoom_sensibility);
			}

			delete e;
		}
	}
}

void Game::draw(float delta)
{
	pp->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	program->use();

	camera->update(player);
	camera->bind(program);

	maze->draw(program);

	pp->draw(pp_program);
}
