#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

class Triangle : public Shape
{
public:
	Shape* clone() {
		return new Triangle(*this);
	}

	Triangle(std::vector<glm::vec3> _vertices, glm::vec3 _center) : Shape(_center), vertices(_vertices)
	{

	}

	Triangle(const Triangle& triangle) : Shape(triangle)
	{
		vertices = triangle.vertices;
		normal = triangle.normal;
	}

	Triangle(std::vector<glm::vec3> _vertices) {
		if (_vertices.size() != 3)
			throw("triangle must have exactly 3 vertices!");
		vertices = _vertices;
		center = (_vertices[0] + _vertices[1] + _vertices[2]) / 3.0f;
		normal = glm::normalize(glm::cross(vertices[1] - vertices[0], vertices[2] - vertices[0]));
	}

	void setWidth(float width)
	{
		vertices[0] = vertices[0] * width;
		vertices[1] = vertices[1] * width;
		vertices[2] = vertices[2] * width;
		center = center * width;
	}

	bool testIntersection(Shape*, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2) ;
	bool testIntersection(Sphere*, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2) ;
	bool testIntersection(Triangle*, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2) ;

	void collisionResponse(Shape*, float dt, const float& timeOfContact, glm::vec3& n, glm::vec3 n2);
	void collisionResponse(Sphere*, float dt, const float& timeOfContact, glm::vec3& n, glm::vec3 n2);
	void collisionResponse(Triangle*, float dt, const float& timeOfContact, glm::vec3& n, glm::vec3 n2);

	Triangle* get() {
		return this;
	}

	AABB getAABB();

	std::vector<glm::vec3> vertices;
	glm::vec3 normal = glm::vec3(0.0);
};

#endif
