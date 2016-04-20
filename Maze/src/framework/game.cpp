#include "game.h"
#include <iostream>
#include "../util/log.h"

std::queue<Event*> Game::events;
bool Game::key_states[1024];
Event* Game::last_mouse = nullptr;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key != GLFW_KEY_UNKNOWN)
		Game::key_states[key] = action != GLFW_RELEASE;
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
		maze = new Maze("maze.bmp");
		program = new Program();

		program->addShader("simple_vertex.glsl", GL_VERTEX_SHADER)
			->addShader("simple_fragment.glsl", GL_FRAGMENT_SHADER);
		program->link();
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
		//if (e->type == EventType::KEY)
		//{
		//	switch (e->key)
		//	{
		//	case GLFW_KEY_D:
		//		camera->Move(Axis::X, delta * move_sensibility);
		//		break;
		//	case GLFW_KEY_A:
		//		camera->Move(Axis::X, delta * -move_sensibility);
		//			break;
		//	case GLFW_KEY_W:
		//		camera->Move(Axis::Y, delta * move_sensibility);
		//		break;
		//	case GLFW_KEY_S:
		//		camera->Move(Axis::Y, delta * -move_sensibility);
		//		break;
		//	}
		//	delete e;
		//}
		//else
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program->use();

	camera->update(player);
	camera->bind(program);

	maze->draw(program);
}
