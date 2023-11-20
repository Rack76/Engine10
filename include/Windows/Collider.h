#ifndef COLLIDER_H
#define COLLIDER_H

#include "Transform.h"
#include "Entity.h"
#include "AABB.h"
#include "Sphere.h"

class CollisionResponseBehavior;
class SetWidthBehavior;
class UpdateColliderBehavior;
class TestIntersectionBehavior;
class GetAABBBehavior;
class StaticSphereCollider;
class DynamicSphereCollider;

class Collider
{
public:
	Collider(EntityId _id);

	Shape* getShape();

	void setId(EntityId _id);

	virtual bool testIntersection(StaticSphereCollider* sphere) = 0;
	virtual bool testIntersection(DynamicSphereCollider* sphere) = 0;

	bool testIntersection(Collider* collider);
	
	void updateCollider();

	void setWidth(float width);

	AABB getAABB();

	void collisionResponse(Collider* collider);

	virtual void collisionResponse(StaticSphereCollider*) = 0;
	virtual void collisionResponse(DynamicSphereCollider*) = 0;
protected:
	Shape* shape;
	EntityId colliderId;
	UpdateColliderBehavior* updateColliderBheavior;
	TestIntersectionBehavior* testIntersectionBehavior;
	GetAABBBehavior* getAABBBehavior;
	SetWidthBehavior* setWidthBehavior;
	CollisionResponseBehavior* collisionResponseBehavior;
};

#endif