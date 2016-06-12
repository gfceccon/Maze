#include "game_scene.h"

Game::Game() : Scene()
{
	try {
		program = new Program();

		program->addShader("shaders/full_vertex.glsl", GL_VERTEX_SHADER)
			->addShader("shaders/full_frag.glsl", GL_FRAGMENT_SHADER);
		program->link();
		maze = new Maze(50, 50);
		maze->init(program);

	} catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		throw;
	}

	player = new Player(maze->getEntryPosition());
	camera = new Camera(Window::width, Window::height);
}

Game::~Game()
{
	delete program;
	delete player;
	delete maze;
	delete camera;
}

void Game::update(float delta)
{
	Scene::update(delta);
	if (Scene::key_states[GLFW_KEY_D] || Scene::key_states[GLFW_KEY_RIGHT]){
        player->applyVelocity(Axis::X, move_sensibility);
	}

	if (Scene::key_states[GLFW_KEY_A] || Scene::key_states[GLFW_KEY_LEFT]){
        player->applyVelocity(Axis::X, -move_sensibility);
	}

	if (Scene::key_states[GLFW_KEY_W] || Scene::key_states[GLFW_KEY_UP]){
        player->applyVelocity(Axis::Z, move_sensibility);
	}

	if (Scene::key_states[GLFW_KEY_S] || Scene::key_states[GLFW_KEY_DOWN]){
        player->applyVelocity(Axis::Z, -move_sensibility);
	}

    player->move(maze, gravity, delta);

	while (Scene::events.size() > 0) {
		Event* e = Scene::events.front();
		Scene::events.pop();
		if (e->type == EventType::MOUSE) {
			camera->addEuler(delta * e->y * rotation_sensibility, delta * e->x * rotation_sensibility, 0.0f);
		} else if (e->type == EventType::SCROLL) {
			if(e->y < 0.0f) {
				camera->zoom(2.0f - zoom_sensibility);
			} else {
				camera->zoom(zoom_sensibility);
			}
		} else if(e->type == EventType::KEY) {
			if (e->action == GLFW_PRESS) {
				switch (e->key)
				{
				case GLFW_KEY_SPACE:
					player->applyVelocity(Axis::Y, move_sensibility * 10);
					break;
				}
			}
		}
		delete e;
	}
}

void Game::draw(float delta)
{
	Scene::draw(delta);
	program->use();

	camera->update(player);
	camera->bind(program);

	maze->draw(program);
}
