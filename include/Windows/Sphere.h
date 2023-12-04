#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "glm/gtc/matrix_transform.hpp"

class Sphere : public Shape
{
public:
	Shape* clone() {
		return new Sphere(*this);
	}

	Sphere(glm::vec3 _center, float _radius) : Shape(_center), radius(_radius)
	{

	}

	Sphere(const Sphere& sphere) : Shape(sphere)
	{
		radius = sphere.radius;
	}

	bool testIntersection(Shape* shape, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2);
	bool testIntersection(Sphere* collider, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2);
	bool testIntersection(Triangle* collider, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2);

	void collisionResponse(Shape*, float dt, const float& timeOfContact, glm::vec3& n, glm::vec3 n2);
	void collisionResponse(Sphere*, float dt, const float& timeOfContact, glm::vec3& n, glm::vec3 n2);
	void collisionResponse(Triangle*, float dt, const float& timeOfContact, glm::vec3& n, glm::vec3 n2);

	void closestPoints(Triangle* triangle, glm::vec3& cp1, glm::vec3& cp2);

	void separateSphere(glm::vec3& center, const glm::vec3& closestPoint, const glm::vec3& normal, const float& radius);

	void setWidth(float width) {
		radius = width;
	}

	AABB getAABB()
	{
		center = Entity::getComponent<Transform>(id)->translation;
		return AABB(glm::vec3(center.x - radius, center.y - radius, center.z - radius),
			glm::vec3(center.x + radius, center.y + radius, center.z + radius));
	}

	Sphere* get()
	{
		return this;
	}



	float radius = 1;
};

#endif