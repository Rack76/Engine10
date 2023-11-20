#ifndef SPHERE_COLLIDER_VISITOR_H
#define SPHERE_COLLIDER_VISITOR_H

#include "ColliderVisitor.h"

class StaticSphereColliderVisitor : public ColliderVisitor
{
public:
	StaticSphereColliderVisitor(Sphere* _shape) {
		shape = _shape;
	}

	void visit(Sphere* sphere) {

	}

private:
	Sphere* shape = nullptr;
};

#endif