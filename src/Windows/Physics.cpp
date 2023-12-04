#include "Physics.h"
#include "Plane.h"
#include <iostream>

void Physics::init()
{
	buildWorldStaticBsp();
}

void Physics::run(float dt)
{
	int i = 0;
	applyGravity(dt);
	buildWorldDynamicBsp();
	dynamicBsp.selfIntersection(dt, collisionList);
	testIntersectionDynamicStatic(dt);
	while (collisionList.size() != 0 && i < 3)
	{
		respondToCollisions(dt);
		buildWorldDynamicBsp();
		dynamicBsp.selfIntersection(dt, collisionList);
		testIntersectionDynamicStatic(dt);
		i++;
	}
	moveRigidBodies(dt);
}

void Physics::terminate()
{
}

void Physics::respondToCollisions(float dt)
{
	auto& pair = collisionList.begin();
	auto collision = pair->second;
	collision.first.first->updateCollider();
	collision.first.first->collisionResponse(collision.first.second, dt, collision.second.timeOfContact, collision.second.n1, collision.second.n2);
	std::map<float, std::pair<std::pair<Collider*, Collider*>, CollisionInfo>> emptyMap;
	collisionList.swap(emptyMap);
}

void Physics::moveRigidBodies(float dt)
{
	auto archetypes = ArchetypeList::getArchetypesWith<RigidBody, Collider>().get();
	for (auto entityType : archetypes)
	{
		auto entities = Entity::getArchetype(entityType.first)->getArray();
		for (auto &entity : *entities)
		{
			auto rigidBody = (RigidBody*)entity.second.at(RigidBody::typeId()).get();
			auto transform = (Transform*)entity.second.at(Transform::typeId()).get();
			auto collider = (Collider*)entity.second.at(Collider::typeId()).get();
			//rigidBody->velocity = rigidBody->velocity + glm::vec3(0.0, -10, 0.0) * 0.0;
			transform->setTranslation(collider->getShape()->center + rigidBody->velocity * dt);
			collider->updateCollider();
		}
	}
}

void Physics::applyGravity(float dt)
{
	//std::cout << dt << std::endl;
	auto archetypes = ArchetypeList::getArchetypesWith<RigidBody>().get();
	for (auto entityType : archetypes)
	{
		auto entities = Entity::getArchetype(entityType.first)->getArray();
		for (auto& entity : *entities)
		{
			auto rigidBody = (RigidBody*)entity.second.at(RigidBody::typeId()).get();
			rigidBody->velocity = rigidBody->velocity + glm::vec3(0.0, -10, 0.0) * dt;
		}
	}
}

void Physics::buildWorldBSP(BSP &bsp, std::vector<Collider*> colliders)
{
	std::vector<AABB> aabbs;
	if (colliders.size() == 0)
		return;
	else if (colliders.size() == 1)
	{
		bsp.aabb = colliders[0]->getAABB();
		bsp.colliders.push_back(colliders[0]);
	
	}
	else
	{
		for (auto collider : colliders)
		{
			aabbs.push_back(collider->getAABB());
		}
		float xMin = std::numeric_limits<float>::max(), yMin = std::numeric_limits<float>::max(), zMin = std::numeric_limits<float>::max();
		float xMax = -std::numeric_limits<float>::max(), yMax = -std::numeric_limits<float>::max(), zMax = -std::numeric_limits<float>::max();

		for (auto &aabb : aabbs)
		{
			if (aabb.p1.x < xMin)
				xMin = aabb.p1.x;
			if (aabb.p1.y < yMin)
				yMin = aabb.p1.y;
			if (aabb.p1.z < zMin)
				zMin = aabb.p1.z;

			if (aabb.p2.x > xMax)
				xMax = aabb.p2.x;
			if (aabb.p2.y > yMax)
				yMax = aabb.p2.y;
			if (aabb.p2.z > zMax)
				zMax = aabb.p2.z;
		}

		bsp.aabb = AABB(glm::vec3(xMin, yMin, zMin), glm::vec3(xMax, yMax, zMax));

		float maxAxisOffset = xMax - xMin;
		float min = xMin, max = xMax;
		glm::vec3 planeNormal = glm::normalize(glm::vec3(maxAxisOffset, 0.0f, 0.0f));
		if (maxAxisOffset < yMax - yMin)
		{
			min = yMin;
			max = yMax;
			maxAxisOffset = yMax - yMin;
			planeNormal = glm::normalize(glm::vec3(0.0f, maxAxisOffset, 0.0f));
		}
		if (maxAxisOffset < zMax - zMin)
		{
			min = zMin;
			max = zMax;
			maxAxisOffset = zMax - zMin;
			planeNormal = glm::normalize(glm::vec3(0.0f, 0.0f, maxAxisOffset));
		}

		glm::vec3 p1 = glm::vec3(xMin, yMin, zMin);
		glm::vec3 p2 = glm::vec3(xMax, yMax, zMax);

		float planeDistance = (min + max) / 2;

		Plane plane(planeNormal, planeDistance);

		std::vector<Collider*> colliderGroup1;
		std::vector<Collider*> colliderGroup2;

		for (auto collider : colliders)
		{
			if (plane.isAbove(collider->getShape()->center))
				colliderGroup1.push_back(collider);
			else
				colliderGroup2.push_back(collider);
		}

		if (colliders.size() == colliderGroup1.size())
		{
			do {
				bsp.colliders.push_back(colliderGroup1[colliderGroup1.size() - 1]);
				colliderGroup1.pop_back();
			} while(colliderGroup1.size() != 0);
		}

		if (colliders.size() == colliderGroup2.size())
		{
			do {
				bsp.colliders.push_back(colliderGroup2[colliderGroup2.size() - 1]);
				colliderGroup2.pop_back();
			} while (colliderGroup2.size() != 0);
		}

		bsp.first = std::make_unique<BSP>();
		bsp.second = std::make_unique<BSP>();

		if (colliderGroup1.size() > 0)
			buildWorldBSP(*bsp.first.get(), colliderGroup1);
		if (colliderGroup2.size() > 0)
			buildWorldBSP(*bsp.second.get(), colliderGroup2);
		return;
	}
}

void Physics::buildWorldStaticBsp()
{
	auto entityTypes = ArchetypeList::getArchetypesWith<Collider>().without<RigidBody>().get();
	std::vector<Collider*> colliders;
	for (auto entityType : entityTypes)
	{
		for (auto &entity : *Entity::getEntityList(entityType.first))
		{
			Collider* collider = (Collider*)entity.second.at(Collider::typeId()).get();
			colliders.push_back(collider);
		}
	}
	buildWorldBSP(staticBsp, colliders);
}

void Physics::buildWorldDynamicBsp()
{
	dynamicBsp.~BSP();
	auto entityTypes = ArchetypeList::getArchetypesWith<Collider, RigidBody>().get();
	std::vector<Collider*> colliders;
	for (auto entityType : entityTypes)
	{
		for (auto &entity : *Entity::getEntityList(entityType.first))
		{
			Collider* collider = (Collider*)entity.second.at(Collider::typeId()).get();
			colliders.push_back(collider);
		}
	}
	buildWorldBSP(dynamicBsp, colliders);
}

void Physics::testIntersectionDynamicStatic(float dt)
{
	auto entityTypes = ArchetypeList::getArchetypesWith<Collider, RigidBody>().get();
	std::vector<Collider*> colliders;
	for (auto entityType : entityTypes)
	{
		for (auto &entity : *Entity::getEntityList(entityType.first))
		{
			Collider* collider = (Collider*)entity.second.at(Collider::typeId()).get();
			staticBsp.testIntersection(collider, dt, collisionList);
		}
	}
}