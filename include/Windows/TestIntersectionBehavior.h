#ifndef TEST_INTERSECTION_BEHAVIOR_H
#define TEST_INTERSECTION_BEHAVIOR_H

#include "Shape.h"
#include "Sphere.h"
#include "Collider.h"
#include "StaticSphereCollider.h"
#include <iostream>
class DynamicSphereCollider;

class TestIntersectionBehavior
{
public:
	virtual bool testIntersection(Collider* shape, Collider* collider) = 0;
	bool dynamicTestIntersectionSphere(Collider* collider1, Collider* collider2)
	{
		std::cout << glm::length(((Sphere*)collider1->getShape())->center - ((Sphere*)collider2->getShape())->center) << std::endl;
		float centerDiff = glm::length(((Sphere*)collider1->getShape())->center - ((Sphere*)collider2->getShape())->center);
		float radiusSum = ((Sphere*)collider1->getShape())->radius + ((Sphere*)collider2->getShape())->radius;
		if (centerDiff - radiusSum < 0)
			return true;
		return false;
	}
};

#endif 