#include <glew.h>
#include "DebugCamera.h"
#include "glm/gtx/transform.hpp"
#include "AssetLoader.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define RADIANS(x) ((x / 180.0f) * (float)M_PI )

void DebugCamera::setOrientation(float mouseMotionX, float mouseMotionY)
{
	rotateCamera(mouseMotionX, mouseMotionY);
	transform =  glm::mat4(orientation);
	setTranslation(translation);
}

void DebugCamera::updateTranslationX(bool forward)
{
	if (forward)
		speedVec = orientation[0] * speed;
	else
		speedVec = orientation[0] * -speed;
}

void DebugCamera::updateTranslationY(bool forward)
{
	if (forward)
		speedVec = orientation[1] * speed;
	else
		speedVec = orientation[1] * -speed;
}

void DebugCamera::updateTranslationZ(bool forward)
{
	if (forward)
		speedVec = orientation[2] * speed;
	else
		speedVec = orientation[2] * -speed;
}

void DebugCamera::rotateCamera(float mouseMotionX, float mouseMotionY)
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

	orientation[0] = xOrientation;
	orientation[1] = yOrientation;
	orientation[2] = zOrientation;
}