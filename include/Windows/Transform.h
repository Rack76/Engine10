#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "AssetLoader.h"
#include "Component.h"
#include "glm/gtc/matrix_transform.hpp"

class Transform : public Counter<Transform>
{
public:
	Transform(EntityId id) : Counter<Transform>(id), orientation(glm::mat3(1.0)),
		translation(glm::vec3(0.0f, 0.0f, 0.0f)), scale(glm::mat3(1.0))
	{

	}

	void setUniform() {
		uniform = glm::mat4(orientation);
		uniform = uniform * glm::mat4(scale);
		uniform = transpose(uniform);
		uniform[3] = glm::vec4(translation, 1.0);
		uniform = transpose(uniform);
	}

	void setScale(float scaleFactor)
	{
		scale = glm::mat3(glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor, scaleFactor, scaleFactor)));
		setUniform();
	}

	void setScale(glm::vec3 scaleVec)
	{
		scale = glm::mat3(glm::scale(glm::mat4(1.0f), scaleVec));
		setUniform();
	}

	void setTranslation(glm::vec3 _translation)
	{
		translation = _translation;
		setUniform();
	}

	glm::mat4 uniform;
	glm::mat3 orientation;
	glm::mat3 scale;
	glm::vec3 translation;
};

#endif