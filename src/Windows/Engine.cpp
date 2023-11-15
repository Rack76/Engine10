#include <glew.h>
#include "Engine.h"
#include "Renderer.h"
#include "Input.h"
#include "DebugCamera.h"

void Engine::init()
{
	glfwInit();
	window = glfwCreateWindow(900, 700, "window", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	Component::registerComponent<Mesh>();
	Component::registerComponent<Shader>();
	Component::registerComponent<Texture>();
	Component::registerComponent<DebugCamera>();

	Renderer::getInstance()->setWindow(window);
	Renderer::getInstance()->init();

	Input::getInstance()->setWindow(window);
	Input::getInstance()->init();
}

void Engine::run()
{
	while (!glfwWindowShouldClose(window))
	{
		for (auto runningSystem : runningSystems)
		{
			runningSystem.second->run();
			glfwPollEvents();
		}
	}
}

void Engine::terminate()
{
	glfwTerminate();
	delete Renderer::getInstance();
	delete Input::getInstance();
}

void Engine::addRunningSystem(int order, System* system)
{
	runningSystems.insert({ order, system });
}

std::map<int, System*> Engine::runningSystems = std::map<int, System*>();
GLFWwindow* Engine::window = nullptr;