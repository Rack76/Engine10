#ifndef STATIC_SPHERE_COLLIDER_H
#define STATIC_SPHERE_COLLIDER_H

#include "StaticCollider.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Sphere.h"

class StatcSphereCollider;
class DynamicSphereCollider;

class StaticSphereCollider : public StaticCollider
{
public:

	StaticSphereCollider(EntityId id);

	bool testIntersection(StaticSphereCollider* _sphere);
	bool testIntersection(DynamicSphereCollider* sphere);
	void collisionResponse(StaticSphereCollider* sphere);
	void collisionResponse(DynamicSphereCollider*);

	~StaticSphereCollider();
};

#endif