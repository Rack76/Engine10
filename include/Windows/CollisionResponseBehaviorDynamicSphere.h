#ifndef COLLISION_RESPONSE_BEHAVIOR_DYNAMIC_SPHERE_H
#define COLLISION_RESPONSE_BEHAVIOR_DYNAMIC_SPHERE_H

#include "CollisionResponseBehavior.h"
#include "DynamicSphereCollider.h"
#include "StaticSphereCollider.h"

class CollisionResponseBehaviorDynamicSphere : public CollisionResponseBehavior
{
public:
	void collisionResponse(Collider* collider1, Collider* collider2) {
		collider2->collisionResponse((DynamicSphereCollider*)collider1);
	}
	void collisionResponse(DynamicSphereCollider* collider1, DynamicSphereCollider* collider2) {

	}
};

#endif 