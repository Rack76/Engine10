#ifndef STATIC_COLLIDER_H
#define STATIC_COLLIDER_H

#include "Component.h"
#include "Collider.h"

class StaticCollider : public Counter<StaticCollider>, public Collider
{
public:

	StaticCollider(EntityId id) : Counter<StaticCollider>(id), 
		Collider(id) {
	}

	virtual bool testIntersection(StaticSphereCollider* sphere) = 0;
	virtual bool testIntersection(DynamicSphereCollider* sphere) = 0;
	virtual void collisionResponse(StaticSphereCollider*) = 0;
	virtual void collisionResponse(DynamicSphereCollider*) = 0;

	void setEntityId(EntityId _id)
	{
		id = _id;
		colliderId = _id;
	}
};

#endif