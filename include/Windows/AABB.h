#ifndef AABB_H
#define AABB_H

#include "glm/gtc/matrix_transform.hpp"

class AABB
{
public:
	AABB(glm::vec3 _p1, glm::vec3 _p2) : p1(_p1), p2(_p2) {

	}

	glm::vec3 p1, p2;
};

#endif 