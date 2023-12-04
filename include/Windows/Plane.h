#ifndef PLANE_H
#define PLANE_H

#include "glm/gtc/matrix_transform.hpp"

class Plane
{
public:
	Plane(glm::vec3 _n, float _d) : n(_n), d(_d) {

	}

	bool isAbove(glm::vec3 point) {
		if (glm::dot(point, n) > d)
			return true;
		return false;
	}

private:
	glm::vec3 n;
	float d;
};

#endif 