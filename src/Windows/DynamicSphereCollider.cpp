#include "DynamicSphereCollider.h"
#include "GetAABBBehaviorSphere.h"
#include "UpdateColliderBehaviorSphere.h"
#include "TestIntersectionBehaviorDynamicSphere.h"
#include "SetWidthBehaviorSphere.h"
#include "CollisionResponseBehaviorDynamicSphere.h"

DynamicSphereCollider::DynamicSphereCollider(EntityId id) : DynamicCollider(id)
{
	shape = new Sphere();
	getAABBBehavior = new GetAABBBehaviorSphere();
	updateColliderBheavior = new UpdateColliderBehaviorSphere();
	testIntersectionBehavior = new TestIntersectionBehaviorDynamicSphere();
	setWidthBehavior = new SetWidthBehaviorSphere();
	collisionResponseBehavior = new CollisionResponseBehaviorDynamicSphere();
}



bool DynamicSphereCollider::testIntersection(StaticSphereCollider* _sphere) {
	return testIntersectionBehavior->dynamicTestIntersectionSphere(this, _sphere);
}

bool DynamicSphereCollider::testIntersection(DynamicSphereCollider* _sphere)
{
	return testIntersectionBehavior->dynamicTestIntersectionSphere(this, _sphere);
}

void DynamicSphereCollider::collisionResponse(StaticSphereCollider* collider)
{ 
	collisionResponseBehavior->collisionResponse(this, collider);
}

void DynamicSphereCollider::collisionResponse(DynamicSphereCollider* collider)
{
	((CollisionResponseBehaviorDynamicSphere*)collisionResponseBehavior)->collisionResponse(this, collider);
}

DynamicSphereCollider::~DynamicSphereCollider()
{
	delete shape;
	delete getAABBBehavior;
	delete updateColliderBheavior;
	delete testIntersectionBehavior;
	delete setWidthBehavior;
	delete collisionResponseBehavior;
}