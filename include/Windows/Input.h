#ifndef INPUT_H
#define INPUT_H

#include <glew.h>
#include "Singleton.h"
#include "System.h"
#include "glfw3.h"

class Input : public Singleton<Input>, public System
{
public:
	void init();
	void run();
	void terminate();
	void setWindow(GLFWwindow* window);
	int getWindowWidth() {
		return windowWidth;
	}
	int getWindowHeight() {
		return windowHeight;
	}

private:
	GLFWwindow* window;
	int windowWidth;
	int windowHeight;
};

#endif