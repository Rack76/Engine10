#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "glm/gtc/matrix_transform.hpp"

class Sphere : public Shape
{
public:

	glm::vec3 center = glm::vec3(0.0f);
	float radius = 1;
};

#endif