#ifndef DYNAMIC_COLLIDER_H
#define DYNAMIC_COLLIDER_H

#include "Collider.h"
#include "Component.h"

class DynamicSphereCollider;
class StaticSphereCollider;

class DynamicCollider : public Counter<DynamicCollider>, public Collider
{
public:
	DynamicCollider(EntityId id) : Counter<DynamicCollider>(id), Collider(id)
	{
	}

	void setEntityId(EntityId _id)
	{
		id = _id;
		colliderId = _id;
	}

	virtual bool testIntersection(DynamicSphereCollider* sphere) = 0;
	virtual bool testIntersection(StaticSphereCollider*) = 0;
	virtual void collisionResponse(StaticSphereCollider*) = 0;
	virtual void collisionResponse(DynamicSphereCollider*) = 0;

};

#endif 