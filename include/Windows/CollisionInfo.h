#ifndef COLLISION_INFO_H
#define COLLISION_INFO_H

#include "glm/gtc/matrix_transform.hpp"

class CollisionInfo
{
public:
	glm::vec3 n1, n2;
	float timeOfContact;
};

#endif