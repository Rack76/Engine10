#ifndef TEST_INTERSECTION_BEHAVIOR_DYNAMIC_SPHERE_H
#define TEST_INTERSECTION_BEHAVIOR_DYNAMIC_SPHERE_H

#include "TestIntersectionBehavior.h"
#include "Collider.h"

class DynamicSphereCollider;

class TestIntersectionBehaviorDynamicSphere : public TestIntersectionBehavior
{
public:
	bool testIntersection(Collider* collider1, Collider* collider2) {
		return collider2->testIntersection((DynamicSphereCollider*)collider1);
	}
};

#endif 