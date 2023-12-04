#ifndef RENDERER_H
#define RENDERER_H

#include <glew.h>
#include "Singleton.h"
#include "System.h"
#include <glfw3.h>
#include "ArchetypeList.h"

class Renderer : public Singleton<Renderer>, public System
{
public:
	void init();
	void run(float dt);
	void terminate();

	void setWindow(GLFWwindow* _window) {
		window = _window;
	}

private:
	void drawDebugObjects();
	void translatePlayerControlledCamera();
	void drawTexturedObjects();
	GLFWwindow* window;
};

#endif 