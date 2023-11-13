#ifndef RENDERER_H
#define RENDERER_H

#include <glew.h>
#include "Singleton.h"
#include "System.h"
#include <glfw3.h>

class Renderer : public Singleton<Renderer>, public System
{
public:
	void init();
	void run();
	void terminate();

	void setWindow(GLFWwindow* _window) {
		window = _window;
	}

private:
	void drawTexturedObjects();

	GLFWwindow* window;
};

#endif 