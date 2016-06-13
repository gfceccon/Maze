#include "test.h"

Test::Test() : Scene()
{
	size = 3.0f;
	angle = 0.0f;
	attConst = 1.0f;
	attLinear = 3.0f;
	attQuad = 0.5f;

	for (int i = 0; i < MAX_TEST_LIGHTS; i++)
		pointLights[i] = PointLight(i, "lights");

	try {
		program = new Program();

		program->addShader("resources/shaders/full_vertex.glsl", GL_VERTEX_SHADER)
			->addShader("resources/shaders/full_frag.glsl", GL_FRAGMENT_SHADER);
		program->link();

	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		throw;
	}

	player = new Player(glm::vec3(0.0f, 0.6 * size, size * 0.5f));
	camera = new Camera(Window::width, Window::height);

	cube = new AdvancedCube(program);
	material = new Material();

	lights = new MultipleLight(MAX_TEST_LIGHTS);
	directional = new DirectionalLight();

	material->initTexture(program, "resources/images/wall.png", Material::TextureType::Diffuse);
	material->initTexture(program, "resources/images/specular.png", Material::TextureType::Specular);
	material->initTexture(program, "resources/images/normal.png", Material::TextureType::Normal);
	//material->initTexture(program, "resources/images/displacementold.png", Material::TextureType::Depth);
	material->initTexture(program, "resources/images/occlusion.png", Material::TextureType::AmbientOcclusion);
	material->setShininess(64.0f);

	pointLights[0].setPosition(0.0f, 0.67f * size, 1.0f);
	//pointLights[0].setPosition(0.0f, 0.0f, 0.0f);
	pointLights[0].setAmbient(0.1f, 0.1f, 0.1f);
	pointLights[0].setDiffuse(1.0f, 1.0f, 1.0f);
	pointLights[0].setSpecular(0.3f, 0.3f, 0.3f);
	pointLights[0].setAttenuation(attConst, attLinear, attQuad);

	directional->setDirection(-1.0f, -1.0f, 0.0f);
	directional->setAmbient(0.05f, 0.05f, 0.05f);
	directional->setDiffuse(0.0f, 0.0f, 0.0f);
	directional->setSpecular(0.0f, 0.0f, 0.0f);

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
	if (Scene::key_states[GLFW_KEY_D] || Scene::key_states[GLFW_KEY_L]) {
		player->move(delta * move_sensibility, 0.0f, 0.0f);
	}

	if (Scene::key_states[GLFW_KEY_A] || Scene::key_states[GLFW_KEY_J]) {
		player->move(-delta * move_sensibility, 0.0f, 0.0f);
	}

	if (Scene::key_states[GLFW_KEY_W] || Scene::key_states[GLFW_KEY_I]) {
		player->move(0.0f, 0.0f, delta * move_sensibility);
	}

	if (Scene::key_states[GLFW_KEY_S] || Scene::key_states[GLFW_KEY_K]) {
		player->move(0.0f, 0.0f, -delta * move_sensibility);
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
				case GLFW_KEY_LEFT:
					attLinear -= 0.1f;
					pointLights[0].setAttenuation(attConst, attLinear, attQuad);
					Log::print(glm::vec3(attConst, attLinear, attQuad));
					break;
				case GLFW_KEY_RIGHT:
					attLinear += 0.1f;
					pointLights[0].setAttenuation(attConst, attLinear, attQuad);
					Log::print(glm::vec3(attConst, attLinear, attQuad));
					break;
				case GLFW_KEY_DOWN:
					attQuad -= 0.1f;
					pointLights[0].setAttenuation(attConst, attLinear, attQuad);
					Log::print(glm::vec3(attConst, attLinear, attQuad));
					break;
				case GLFW_KEY_UP:
					attQuad += 0.1f;
					pointLights[0].setAttenuation(attConst, attLinear, attQuad);
					Log::print(glm::vec3(attConst, attLinear, attQuad));
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
	directional->bind(program);

	//cube->loadIdentity();
	//cube->translate(0.0f, 0.0f, 5.0f);
	//cube->rotate(angle, 0, 1, 0);
	//cube->translate(-size * 0.5f, -size * 0.5f, -size * 0.5f);
	//cube->scale(size, size, size);
	//cube->bind(program);
	//cube->draw();
	//angle += delta * 20.0f;
	lights->clear();

	for (int i = -10; i < 10; i++)
	{
		if (i == -2)
			lights->addLight(&pointLights[0]);
		else if (i == 1)
			lights->clear();

		lights->bind(program);
		cube->loadIdentity();
		cube->translate(i * (size + 0.0f) + size * 0.5f, 0.0f, size);
		cube->scale(size, size, size);
		cube->bind(program);
		cube->draw();

		cube->loadIdentity();
		cube->translate(i * (size + 0.0f) + size * 0.5f, -size, 0.0f);
		cube->scale(size, size, size);
		cube->bind(program);
		cube->draw();

		cube->loadIdentity();
		cube->translate(i * (size + 0.0f) + size * 0.5f, 0.0f, -size);
		cube->scale(size, size, size);
		cube->bind(program);
		cube->draw();
	}
}
