#include "test.h"


Test::Test() : Scene()
{
	for (int i = 0; i < MAX_MAZE_LIGHTS; i++)
		pointLights[i] = PointLight(i, "lights");

	try {
		program = new Program();

		program->addShader("resources/shaders/test_vertex.glsl", GL_VERTEX_SHADER)
			->addShader("resources/shaders/test_frag.glsl", GL_FRAGMENT_SHADER);
		program->link();

	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		throw;
	}

	player = new Player(glm::vec3(5.0f, 5.0f, 5.0f));
	camera = new Camera(Window::width, Window::height);

	cube = new AdvancedCube(program);
	material = new Material();

	lights = new MultipleLight(MAX_TEST_LIGHTS);
	directional = new DirectionalLight();

	lights->clear();
	lights->addLight(&pointLights[0]);

	material->initTexture(program, "resources/images/wall.png", Material::TextureType::Diffuse);
	material->setShininess(64.0f);
	pointLights[0].setPosition(0.0f, 0.0f, 5.0f);
	directional->setDirection(-0.5f, -0.5f, 0.0f);
}

Test::~Test()
{
	delete program;
	delete player;
	delete camera;
	delete lights;
	delete directional;
}

void Test::update(float delta)
{
	Scene::update(delta);
	if (Scene::key_states[GLFW_KEY_D] || Scene::key_states[GLFW_KEY_RIGHT]) {
		player->move(move_sensibility, 0.0f, 0.0f);
	}

	if (Scene::key_states[GLFW_KEY_A] || Scene::key_states[GLFW_KEY_LEFT]) {
		player->move(-move_sensibility, 0.0f, 0.0f);
	}

	if (Scene::key_states[GLFW_KEY_W] || Scene::key_states[GLFW_KEY_UP]) {
		player->move(0.0f, 0.0f, move_sensibility);
	}

	if (Scene::key_states[GLFW_KEY_S] || Scene::key_states[GLFW_KEY_DOWN]) {
		player->move(0.0f, 0.0f, -move_sensibility);
	}

	while (Scene::events.size() > 0) {
		Event* e = Scene::events.front();
		Scene::events.pop();
		if (e->type == EventType::MOUSE) {
			camera->addEuler(delta * e->y * rotation_sensibility, delta * e->x * rotation_sensibility, 0.0f);
		}
		else if (e->type == EventType::SCROLL) {
			if (e->y < 0.0f) {
				camera->zoom(2.0f - zoom_sensibility);
			}
			else {
				camera->zoom(zoom_sensibility);
			}
		}
		else if (e->type == EventType::KEY) {
			if (e->action == GLFW_PRESS) {
				switch (e->key)
				{
				case GLFW_KEY_SPACE:
					player->applyVelocity(Axis::Y, move_sensibility * 10);
					break;
				case GLFW_KEY_ESCAPE:
					close();
					break;
				}
			}
		}
		delete e;
	}
}

void Test::draw(float delta)
{
	Scene::draw(delta);
	program->use();

	camera->update(player);
	camera->bind(program);

	material->bind(program);
	lights->bind(program);
	directional->bind(program);

	//cube->loadIdentity();
	cube->rotate(1.0f, 1, 1, 0);
	cube->bind(program);
	cube->draw();
}
