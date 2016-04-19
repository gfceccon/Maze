#include "game.h"

#include <util/log.h>

std::queue<Event*> Game::events;
bool Game::keyStates[1024];
Event* Game::lastMouse = nullptr;

Game::Game(int width, int height)
{
	maze = new Maze("maze.bmp");
	camera = new Camera(width, height);
	program = new Program();

	program->AddShader("simple_vertex.glsl", GL_VERTEX_SHADER)
		->AddShader("simple_fragment.glsl", GL_FRAGMENT_SHADER);
	program->Link();
	camera->Move(-24.0f, 0.5f, 1.0f);
}


Game::~Game()
{
	if (lastMouse)
		delete lastMouse;
	delete program;
	delete maze;
	delete camera;
}


void Game::SetClearColor(Color& color)
{
	this->clear = color;
	glClearColor(clear.r, clear.g, clear.b, clear.a);
}



void Game::Update(float delta)
{
	if (Game::keyStates[GLFW_KEY_D])
		camera->Move(Axis::X, delta * moveSensibility);
	if (Game::keyStates[GLFW_KEY_A])
		camera->Move(Axis::X, delta * -moveSensibility);
	if (Game::keyStates[GLFW_KEY_W])
		camera->Move(Axis::Z, delta * moveSensibility);
	if (Game::keyStates[GLFW_KEY_S])
		camera->Move(Axis::Z, delta * -moveSensibility);

	while (events.size() > 0)
	{
		Event* e = events.front();
		events.pop();
		//if (e->type == EventType::KEY)
		//{
		//	switch (e->key)
		//	{
		//	case GLFW_KEY_D:
		//		camera->Move(Axis::X, delta * moveSensibility);
		//		break;
		//	case GLFW_KEY_A:
		//		camera->Move(Axis::X, delta * -moveSensibility);
		//			break;
		//	case GLFW_KEY_W:
		//		camera->Move(Axis::Y, delta * moveSensibility);
		//		break;
		//	case GLFW_KEY_S:
		//		camera->Move(Axis::Y, delta * -moveSensibility);
		//		break;
		//	}
		//	delete e;
		//}
		//else
		if (e->type == EventType::MOUSE)
		{
			if (lastMouse == nullptr)
			{
				lastMouse = e;
				continue;
			}
			double deltaX = e->x - lastMouse->x;
			double deltaY = lastMouse->y - e->y;

			camera->AddEuler(delta * deltaY * rotationSensibility, delta * deltaX * rotationSensibility, 0.0f);

			delete lastMouse;
			lastMouse = e;
		}
		else if (e->type == EventType::SCROLL)
		{
			if(e->y < 0.0f)
				camera->Zoom(2.0f - zoomSensibility);
			else
				camera->Zoom(zoomSensibility);

			delete e;
		}
	}
}

void Game::Draw(float delta)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program->Use();

	camera->Bind(program);

	maze->Draw(program);
}


void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key != GLFW_KEY_UNKNOWN)
		Game::keyStates[key] = action != GLFW_RELEASE;
	//else
	//	Game::events.push(new Event(key, scancode, action, mods));
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	Game::events.push(new Event(xpos, ypos));
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Game::events.push(new Event(xoffset, yoffset, true));
}