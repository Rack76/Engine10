#ifndef COLLISION_RESPONSE_BEHAVIOR_STATIC_SPHERE_H
#define COLLISION_RESPONSE_BEHAVIOR_STATIC_SPHERE_H

#include "CollisionResponseBehavior.h"
#include "Collider.h"

class StaticSphereCollider;
class DynamicSphereCollider;

class CollisionResponseBehaviorStaticSphere : public CollisionResponseBehavior
{
public:
	void collisionResponse(Collider* collider1, Collider* collider2)
	{
		collider2->collisionResponse((StaticSphereCollider*)collider1);
	}

	void collisionResponse(StaticSphereCollider* sphere1, StaticSphereCollider* sphere2) {

	}
};

#endif 