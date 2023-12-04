#ifndef AABB_H
#define AABB_H

#include "glm/gtc/matrix_transform.hpp"

class AABB
{
public:
	AABB() {

	}

	bool testIntersection(const AABB& aabb) {
		float xAxisOffset2 = aabb.p2.x - aabb.p1.x;
		float yAxisOffset2 = aabb.p2.y - aabb.p1.y;
		float zAxisOffset2 = aabb.p2.z - aabb.p1.z;

		float xAxisOffset1 = p2.x - p1.x;
		float yAxisOffset1 = p2.y - p1.y;
		float zAxisOffset1 = p2.z - p1.z;

		float xDistance = p1.x - aabb.p1.x;
		float yDistance = p1.y - aabb.p1.y;
		float zDistance = p1.z - aabb.p1.z;

		if (xDistance < xAxisOffset2 && -xDistance < xAxisOffset1)
			if (yDistance < yAxisOffset2 && -yDistance < yAxisOffset1)
				if (zDistance < zAxisOffset2 && -zDistance < zAxisOffset1)
					return true;

		return false;
	}

	AABB(glm::vec3 _p1, glm::vec3 _p2) : p1(_p1), p2(_p2) {

	}

	glm::vec3 p1, p2;
};

#endif 