#include <glew.h>
#include "Engine.h"
#include "Renderer.h"
#include "Input.h"
#include "Physics.h"

void Engine::init()
{
	auto result = glfwInit();
	window = glfwCreateWindow(900, 700, "window", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();

	Component::registerComponent<Mesh>();
	Component::registerComponent<Shader>();
	Component::registerComponent<Texture>();
	Component::registerComponent<DebugCamera>();
	Component::registerComponent<Transform>();
	Component::registerComponent<StaticSphereCollider>();
	Component::registerComponent<DynamicSphereCollider>();
	Component::registerComponent<PlayerInput>();

	Renderer::getInstance()->setWindow(window);
    Input::getInstance()->setWindow(window);

	Engine::addRunningSystem(0, Physics::getInstance());
	Engine::addRunningSystem(1, Renderer::getInstance());
}

void Engine::run()
{
	Renderer::getInstance()->init();
	Input::getInstance()->init();
	Physics::getInstance()->init();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		for (auto runningSystem : runningSystems)
		{
			runningSystem.second->run();
		}
	}
}

void Engine::terminate()
{
	glfwTerminate();
	delete Renderer::getInstance();
	delete Input::getInstance();
	delete Physics::getInstance();
}

void Engine::addRunningSystem(int order, System* system)
{
	runningSystems.insert({ order, system });
}

std::map<int, System*> Engine::runningSystems = std::map<int, System*>();
GLFWwindow* Engine::window = nullptr;