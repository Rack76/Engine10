#ifndef CAMERA_H
#define CAMERA_H

#include <glew.h>
#include <map>
#include "glm/gtc/matrix_transform.hpp"
#include "AssetLoader.h"

using EntityIndex = int;
using EntityType = unsigned long;
using EntityId = std::pair<EntityType, EntityIndex>;

#define _USE_MATH_DEFINES
#include <math.h>

#define RADIANS(x) ((x / 180.0f) * (float)M_PI )

class Camera
{
public:
	
	Camera() : perspective(glm::perspective(1.5f, 1.0f, 0.50f, 50.0f)),  transform(glm::mat4(1.0)), orientation(glm::mat3(1.0)), translation(glm::vec3(0.0f, 0.0f, 4.0f)), speedVec(glm::vec3(0.0f))
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

	void setTransform() {
		auto programs = AssetLoader::getPrograms();
		for (auto program : programs)
		{
			glUseProgram(program.second);
			GLint location = glGetUniformLocation(program.second, "cameraTransform");
			glUniformMatrix4fv(location, 1, GL_FALSE, &transform[0][0]);
			GLfloat* tab = new float[16];
			glGetUniformfv(program.second, glGetUniformLocation(program.second, "perspective"), tab);
			float value = tab[11];
			delete[]tab;
		}
	}

	virtual void setOrientation(glm::mat3 _orientation) {
		orientation = _orientation;
	}

	virtual void setTranslation(glm::vec3 _translation) {
		translation = _translation;
		glm::vec3 rotatedTranslation =   -translation  * orientation;
		transform = glm::transpose(transform);
		transform[3] = glm::vec4(rotatedTranslation, 1.0f);
		transform = glm::transpose(transform);
		setTransform();
	}

	glm::vec3 getSpeedVec() {
		return speedVec;
	}

	glm::mat3 getTransform() {
		return transform;
	}

	glm::mat3 getOrientation() {
		return orientation;
	}

	glm::vec3 getTranslation() {
		return translation;
	}

private:
	//static EntityId activeCameraOwner;

protected:

	glm::mat4 transform;
	glm::mat4 perspective;
	glm::mat3 orientation;
	glm::vec3 translation;
	glm::vec3 speedVec;
	float speed = 0.01f;
};

#endif 