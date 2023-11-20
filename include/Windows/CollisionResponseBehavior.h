#ifndef COLLISION_RESPONSE_BEHAVIOR_H
#define COLLISION_RESPONSE_BEHAVIOR_H

#include "glm/gtc/matrix_transform.hpp"
#include "DynamicSphereCollider.h"
#include "Entity.h"
#include "Shape.h"
class Collider;

class CollisionResponseBehavior
{
public:
	virtual void collisionResponse(Collider* collider1, Collider* collider2) = 0;
	void dynamic_staticCollisionResponseSphere(DynamicSphereCollider* collider1, StaticSphereCollider* collider2) {
		Sphere* sphere1 = (Sphere*)collider1->getShape();
		Sphere* sphere2 = (Sphere*)collider2->getShape();
		float radiusSum = sphere1->radius + sphere2->radius;
		glm::vec3 centerDiff = sphere1->center - sphere2->center;
		float depth = radiusSum - glm::length(centerDiff);
		glm::vec3 separatingVec = glm::normalize(centerDiff) * depth;
		sphere1->center = sphere1->center + separatingVec;
		auto transform = Entity::getComponent<Transform>(collider1->getEntityId());
		transform->setTranslation(sphere1->center);
	}
};

#endif 