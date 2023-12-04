#ifndef  SHAPE_H
#define SHAPE_H

#include "Entity.h"
#include "Transform.h"
#include "AABB.h"
class Sphere;
class Triangle;

class Shape
{
public:
	virtual Shape* clone() = 0;

	Shape() {

	}

	Shape(glm::vec3 _center) : center(_center) {

	}

	Shape(const Shape& shape)
	{
		id = shape.id;
		center = shape.center;
	}

	virtual bool testIntersection(Shape*, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2) = 0;
	virtual bool testIntersection(Sphere*, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2) = 0;
	virtual bool testIntersection(Triangle*, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2) = 0;

	virtual void collisionResponse(Shape*, float dt, const float& timeOfContact, glm::vec3 &n, glm::vec3 n2) = 0;
	virtual void collisionResponse(Sphere*, float dt, const float& timeOfContact, glm::vec3 &n, glm::vec3 n2) = 0;
	virtual void collisionResponse(Triangle*, float dt, const float& timeOfContact, glm::vec3 &n, glm::vec3 n2) = 0;

	virtual void setWidth(float width) = 0;

	virtual AABB getAABB() = 0;

	void update(EntityId id) {
		auto transform = Entity::getComponent<Transform>(id);
		center = transform->translation;
	}

	virtual ~Shape() {

	}

	EntityId id;

	glm::vec3 center = glm::vec3(0.0);
};

#endif
