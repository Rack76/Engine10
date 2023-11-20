#ifndef DYNAMIC_SPHERE_COLLIDER_H
#define DYNAMIC_SPHERE_COLLIDER_H

#include "DynamicCollider.h"



class DynamicSphereCollider : public DynamicCollider
{
public:
	DynamicSphereCollider(EntityId id);

	bool testIntersection(StaticSphereCollider* sphere);
	bool testIntersection(DynamicSphereCollider* sphere);
	void collisionResponse(StaticSphereCollider*);
	void collisionResponse(DynamicSphereCollider*);

	~DynamicSphereCollider();
};

#endif