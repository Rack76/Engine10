#include <glew.h>
#include "DebugCamera.h"
#include "glm/gtx/transform.hpp"
#include "AssetLoader.h"
#include "Entity.h"
#include "Transform.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define RADIANS(x) ((x / 180.0f) * (float)M_PI )

void DebugCamera::setUniformTranslation()
 {
 auto transform = Entity::getComponent<Transform>(id);
 glm::vec3 rotatedTranslation = -transform->translation * transform->orientation;
 uniform = glm::transpose(uniform);
 uniform[3] = glm::vec4(rotatedTranslation, 1.0f);
 uniform = glm::transpose(uniform);
 setUniform();
}

void DebugCamera::setUniformRotation(float mouseMotionX, float mouseMotionY)
{
	static double xAxisAngle = 0;
	static double yAxisAngle = 0;
	xAxisAngle += mouseMotionY;
	yAxisAngle -= mouseMotionX;

	if (xAxisAngle > 89)
		xAxisAngle = 89;
	else if (xAxisAngle < -89)
		xAxisAngle = -89;

	glm::vec3 zOrientation = glm::vec3(sin(RADIANS(yAxisAngle)) * cos(RADIANS(xAxisAngle)), sin(RADIANS(xAxisAngle)), cos(RADIANS(xAxisAngle)) * cos(RADIANS(yAxisAngle)));
	glm::vec3 xOrientation = glm::normalize(glm::cross(glm::vec3(0.0, 1.0, 0.0), zOrientation));
	glm::vec3 yOrientation = glm::normalize(glm::cross(zOrientation, xOrientation));

	auto transform = Entity::getComponent<Transform>(id);

	transform->orientation[0] = xOrientation;
	transform->orientation[1] = yOrientation;
	transform->orientation[2] = zOrientation;
	uniform = glm::mat4(transform->orientation);
	setUniform();
}