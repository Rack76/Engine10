#ifndef CAMERA_H
#define CAMERA_H

#include <glew.h>
#include <map>
#include "glm/gtc/matrix_transform.hpp"
#include "AssetLoader.h"
#include "Input.h"

using EntityIndex = int;
using EntityType = unsigned long;
using EntityId = std::pair<EntityType, EntityIndex>;

#define _USE_MATH_DEFINES
#include <math.h>

#define RADIANS(x) ((x / 180.0f) * (float)M_PI )

class Camera
{
public:
	
	Camera() : perspective(glm::perspective(1.5f, (float)Input::getInstance()->getWindowWidth() / (float)Input::getInstance()->getWindowHeight(), 0.5f, 50.0f)), 
		uniform(glm::mat4(1.0)), speedVec(glm::vec3(0.0f))
	{
		auto programs = AssetLoader::getPrograms();
		for (auto program : programs)
		{
			glUseProgram(program.second);
			GLint location = glGetUniformLocation(program.second, "perspective");
			glUniformMatrix4fv(location, 1, GL_FALSE, &perspective[0][0]);
		}
	}

	/*static void setActiveCameraOwner(EntityId id)
	{
		activeCameraOwner = id;
	}*/

	void stopCamera () {
		speedVec = glm::vec3(0.0f);
	}

	void setUniform() {
		auto programs = AssetLoader::getPrograms();
		for (auto program : programs)
		{
			glUseProgram(program.second);
			GLint location = glGetUniformLocation(program.second, "cameraTransform");
			glUniformMatrix4fv(location, 1, GL_FALSE, &uniform[0][0]);
		}
	}

	glm::vec3 getSpeedVec() {
		return speedVec;
	}

	glm::mat3 getUniform() {
		return uniform;
	}

private:
	//static EntityId activeCameraOwner;

protected:

	glm::mat4 uniform;
	glm::mat4 perspective;
	glm::vec3 speedVec;
	float speed = 0.03f;
};

#endif 