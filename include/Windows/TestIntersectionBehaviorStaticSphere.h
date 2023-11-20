#ifndef TEST_INTERSECTION_BEHAVIOR_STATIC_SPHERE_H
#define TEST_INTERSECTION_BEHAVIOR_STATIC_SPHERE_H

#include "TestIntersectionBehavior.h"
#include "Collider.h"

class TestIntersectionBehaviorStaticSphere : public TestIntersectionBehavior
{
public:
	bool testIntersection(Collider* collider1, Collider* collider2) {
		return collider2->testIntersection((StaticSphereCollider*)collider1);
	}

	bool testIntersection(StaticSphereCollider* sphere1, StaticSphereCollider* sphere2)
	{
		return false;
	}
};

#endif