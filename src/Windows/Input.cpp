#include "Input.h"
#include <map>
#include "Entity.h"
#include "PlayerControlledCamera.h"

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void Input::setWindow(GLFWwindow* _window)
{
	window = _window;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
}

void Input::init()
{
	
	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetKeyCallback(window, key_callback);
}

void Input::run()
{

}

void Input::terminate()
{

}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

	int windowWidth;
	int windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	double xOffset = xpos - (double)windowWidth / 2.0;
	double yOffset = ypos - (double)windowHeight / 2.0;

	auto cameraOwner = PlayerControlledCamera::getActivePlayerControlledCameraOwner();
	auto camera = Entity::getComponent<PlayerControlledCamera>(cameraOwner);
	camera->setOrientation(xOffset, yOffset);

	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::map<int, std::map<int, int>> sKeyStates;
	sKeyStates[glfwGetKey(window, GLFW_KEY_W)].insert({ GLFW_KEY_W , GLFW_KEY_W });
	sKeyStates[glfwGetKey(window, GLFW_KEY_D)].insert({ GLFW_KEY_D , GLFW_KEY_D });
	sKeyStates[glfwGetKey(window, GLFW_KEY_A)].insert({ GLFW_KEY_A , GLFW_KEY_A });
	sKeyStates[glfwGetKey(window, GLFW_KEY_S)].insert({ GLFW_KEY_S , GLFW_KEY_S });
	sKeyStates[glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)].insert({ GLFW_KEY_LEFT_SHIFT , GLFW_KEY_LEFT_SHIFT });
	sKeyStates[glfwGetKey(window, GLFW_KEY_SPACE)].insert({ GLFW_KEY_SPACE , GLFW_KEY_SPACE });

	PlayerControlledCamera* camera = Entity::getComponent<PlayerControlledCamera>(PlayerControlledCamera::getActivePlayerControlledCameraOwner());

	static int lastKeyPress = -1;
	//int newKeyPress = -1;

	if (sKeyStates.find(GLFW_PRESS) == sKeyStates.end())
	{
		camera->stopCamera();
		lastKeyPress = -1;
		return;
	}

	if (sKeyStates.at(GLFW_PRESS).size() == 1)
		lastKeyPress = sKeyStates.at(GLFW_PRESS).begin()->first;

	if (!camera)
	{
		std::cerr << "no active PlayerControlledCamera component!" << std::endl;
		return;
	}

	switch (lastKeyPress)
	{
	case GLFW_KEY_W:
		camera->updateTranslationZ(false);
		break;
	case GLFW_KEY_S:
		camera->updateTranslationZ(true);
		break;
	case GLFW_KEY_A:
		camera->updateTranslationX(false);
		break;
	case GLFW_KEY_D:
		camera->updateTranslationX(true);
		break;
	case GLFW_KEY_LEFT_SHIFT:
		camera->updateTranslationY(false);
		break;
	case GLFW_KEY_SPACE:
		camera->updateTranslationY(true);
		break;
	}
}