#include "Collider.h"
#include "TestIntersectionBehavior.h"
#include "UpdateColliderBehavior.h"
#include "SetWidthBehavior.h"
#include "GetAABBBehavior.h"
#include "CollisionResponseBehavior.h"

Collider::Collider(EntityId _id) : colliderId(_id), shape(nullptr)
{

}

Shape* Collider::getShape()
{
	return shape;
}

void Collider::setId(EntityId _id)
{
	colliderId = _id;
}

bool Collider::testIntersection(Collider* collider)
{
	return testIntersectionBehavior->testIntersection(this, collider);
}

void Collider::updateCollider() {
	updateColliderBheavior->updateCollider(shape, colliderId);
}

void Collider::setWidth(float width)
{
	setWidthBehavior->setWidth(shape, width);
}

AABB Collider::getAABB() {
	return getAABBBehavior->getAABB(shape);
}

void Collider::collisionResponse(Collider* collider) {
	collisionResponseBehavior->collisionResponse(this, collider);
}