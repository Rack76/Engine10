#include <glew.h>
#include "Engine.h"
#include "Renderer.h"

void Engine::init()
{
	glfwInit();
	window = glfwCreateWindow(900, 700, "window", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	Renderer::getInstance()->setWindow(window);
	Renderer::getInstance()->init();

	Component::registerComponent<Mesh>(); 
	Component::registerComponent<Shader>();
	Component::registerComponent<Texture>();
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
}

void Engine::addRunningSystem(int order, System* system)
{
	runningSystems.insert({ order, system });
}

std::map<int, System*> Engine::runningSystems = std::map<int, System*>();
GLFWwindow* Engine::window = nullptr;