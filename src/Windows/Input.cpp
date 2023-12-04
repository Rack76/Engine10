#include "Input.h"
#include <map>
#include "Entity.h"
#include "PlayerControlledCamera.h"
#include "PlayerInput.h"

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void Input::setWindow(GLFWwindow* _window)
{
	window = _window;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
}

void Input::init()
{
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetKeyCallback(window, key_callback);
}

void Input::run(float dt)
{
	glfwPollEvents();
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
	camera->setUniformRotation(xOffset, yOffset);

	glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	PlayerControlledCamera* camera = Entity::getComponent<PlayerControlledCamera>(PlayerControlledCamera::getActivePlayerControlledCameraOwner());

	int translateKey = -1;
	static int keyCount = 0;

	switch (action)
	{
	case GLFW_PRESS:
		keyCount++;
		break;
	case GLFW_RELEASE:
		keyCount--;
		break;
	}

		switch (key)
		{
		case GLFW_KEY_W:
			switch (glfwGetKey(window, key))
			{
			case GLFW_PRESS:
				if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
					camera->updateTranslationSpeedZ(false);
				break;

			case GLFW_RELEASE:
				if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
					camera->updateTranslationSpeedZ(true);
				if (keyCount == 0)
					camera->stopCamera();
				break;
			}
			break;
		case GLFW_KEY_S:
			switch (glfwGetKey(window, key))
			{
			case GLFW_PRESS:
				if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
					camera->updateTranslationSpeedZ(true);
				break;

			case GLFW_RELEASE:
				if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
					camera->updateTranslationSpeedZ(false);
				if (keyCount == 0)
					camera->stopCamera();
				break;
			}
			break;
		case GLFW_KEY_A:
			switch (glfwGetKey(window, key))
			{
			case GLFW_PRESS:
				if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
					camera->updateTranslationSpeedX(false);
				break;

			case GLFW_RELEASE:
				if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
					camera->updateTranslationSpeedX(true);
				if (keyCount == 0)
					camera->stopCamera();
				break;
			}
			break;
		case GLFW_KEY_D:
			switch (glfwGetKey(window, key))
			{
			case GLFW_PRESS:
				if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
					camera->updateTranslationSpeedX(true);
				break;

			case GLFW_RELEASE:
				if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
					camera->updateTranslationSpeedX(false);
				if (keyCount == 0)
					camera->stopCamera();
				break;
			}
			break;
		case GLFW_KEY_LEFT_SHIFT:
			switch (glfwGetKey(window, key))
			{
			case GLFW_PRESS:
				if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
					camera->updateTranslationSpeedY(true);
				break;

			case GLFW_RELEASE:
				if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
					camera->updateTranslationSpeedY(false);
				if (keyCount == 0)
					camera->stopCamera();
				break;
			}
			break;
		case GLFW_KEY_SPACE:
			switch (glfwGetKey(window, key))
			{
			case GLFW_PRESS:
				if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
					camera->updateTranslationSpeedY(false);
				break;

			case GLFW_RELEASE:
				if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
					camera->updateTranslationSpeedY(true);
				if (keyCount == 0)
					camera->stopCamera();
				break;
			}
			break;
		case GLFW_KEY_RIGHT:
			if (glfwGetKey(window, key) == GLFW_PRESS)
				translateKey = KEY_RIGHT;
			else
				translateKey = -1;
			break;
		case GLFW_KEY_LEFT:
			if (glfwGetKey(window, key) == GLFW_PRESS)
				translateKey = KEY_LEFT;
			else
				translateKey = -1;
			break;
		case GLFW_KEY_UP:
			if (glfwGetKey(window, key) == GLFW_PRESS)
				translateKey = KEY_UP;
			else
				translateKey = -1;
			break;
		case GLFW_KEY_DOWN:
			if (glfwGetKey(window, key) == GLFW_PRESS)
				translateKey = KEY_DOWN;
			else
				translateKey = -1;
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		}


	

	auto archetypeIds = ArchetypeList::getArchetypesWith<PlayerInput>().get();
	for (auto archetypeId : archetypeIds)
	{
		auto entityList = Entity::getEntityList(archetypeId.first);
		for (auto& entity : *entityList)
		{
			auto& components = entity.second;

			PlayerInput* playerInput = (PlayerInput*)components.at(PlayerInput::typeId()).get();
			Transform* transform = (Transform*)components.at(Transform::typeId()).get();
			//if(translateKeyPress != -1)
			playerInput->runActions(translateKey, {});
		}
	}
}