#ifndef COLLIDER_VISITOR_H
#define COLLIDER_VISITOR_H

#include "Sphere.h"

class Collider;

class ColliderVisitor
{
public:
	virtual void visit(Sphere*) = 0;
};

#endif