#include "StaticSphereCollider.h"
#include "DynamicSphereCollider.h"
#include "Transform.h"
#include "Entity.h"
#include "CollisionResponseBehaviorStaticSphere.h"
#include "GetAABBBehaviorSphere.h"
#include "UpdateColliderBehaviorSphere.h"
#include "TestIntersectionBehaviorStaticSphere.h"
#include "SetWidthBehaviorSphere.h"

StaticSphereCollider::StaticSphereCollider(EntityId id) : StaticCollider(id)
{
	shape = new Sphere();
	getAABBBehavior = new GetAABBBehaviorSphere();
	updateColliderBheavior = new UpdateColliderBehaviorSphere();
	testIntersectionBehavior = new TestIntersectionBehaviorStaticSphere();
	setWidthBehavior = new SetWidthBehaviorSphere();
	collisionResponseBehavior = new CollisionResponseBehaviorStaticSphere();
}

bool StaticSphereCollider::testIntersection(StaticSphereCollider* _sphere)
{
	return ((TestIntersectionBehaviorStaticSphere*)testIntersectionBehavior)->testIntersection(this, _sphere);
}

bool StaticSphereCollider::testIntersection(DynamicSphereCollider* sphere) {
	return testIntersectionBehavior->dynamicTestIntersectionSphere(this, sphere);
}

void StaticSphereCollider::collisionResponse(StaticSphereCollider* collider) {
	((CollisionResponseBehaviorStaticSphere*)collisionResponseBehavior)->collisionResponse(this, collider);
}

void StaticSphereCollider::collisionResponse(DynamicSphereCollider* collider)
{
	collisionResponseBehavior->dynamic_staticCollisionResponseSphere(collider, this);
}

StaticSphereCollider::~StaticSphereCollider()
{
	delete shape;
	delete getAABBBehavior;
	delete updateColliderBheavior;
	delete testIntersectionBehavior;
	delete setWidthBehavior;
	delete collisionResponseBehavior;
}