#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include "Component.h"
#include "glm/gtc/matrix_transform.hpp"

class RigidBody: public Counter<RigidBody>
{
public:
	RigidBody(EntityId id) : Counter<RigidBody>(id)
	{

	}
	glm::vec3 velocity = glm::vec3(0.0);
};

#endif 