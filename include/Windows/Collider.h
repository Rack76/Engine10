#ifndef COLLIDER_H
#define COLLIDER_H

#include "Transform.h"
#include "Entity.h"
#include "AABB.h"
#include "Shape.h"

class Collider : public Counter<Collider>
{
public:

	Collider(EntityId id) : Counter<Collider>(id)
	{

	}

	Collider(const Collider& collider) : Counter<Collider>(collider)
	{
		shape = collider.shape->clone();
	}

	template <typename T>
	void setShape(T _shape)
	{
		if (shape)
		{
			Shape* temp = shape;
			shape = new T(_shape);
			shape->id = id;
			delete temp;
		}
		else
		{
			shape = new T(_shape);
			shape->id = id;
		}
	}

	Shape* getShape()
	{
		return shape;
	}

	bool testIntersection(Collider* collider, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2)
	{
		return collider->shape->testIntersection(shape, dt, firstTimeOfContact, n1, n2);
	}
	
	void updateCollider() {
		shape->update(id);
	}

	void setEntityId(EntityId _id)
	{
		id = _id;
		shape->id = _id;
	}

	void setWidth(float width)
	{
		shape->setWidth(width);
	}

	AABB getAABB() {
		//updateCollider();
		return shape->getAABB();
	}

	void collisionResponse(Collider* collider, float dt, const float &timeOfContact, glm::vec3 n, glm::vec3 n2) {
		collider->shape->collisionResponse(shape,dt, timeOfContact, n, n2);
	}

	~Collider()
	{
		if (shape)
			delete shape;
	}

private:
	Shape* shape = nullptr;
};

#endif