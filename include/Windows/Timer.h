#ifndef TIMER_H
#define TIMER_H

#include "glfw3.h"

class Timer
{
public:
	void reset()
	{
		lastTime = glfwGetTime();
	}

	float getTime()
	{
		float value = glfwGetTime();
		return value - lastTime;
	}
	float lastTime = 0;
};

#endif 