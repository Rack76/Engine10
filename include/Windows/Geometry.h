#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "glm/gtc/matrix_transform.hpp"
#include <vector>

class Geometry
{
public:
	std::vector<glm::vec3> triangles;
	std::vector<glm::vec3> vertices;
};

#endif 
