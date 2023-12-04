#include "BSP.h"

void BSP::selfIntersection(float dt, std::map<float, std::pair<std::pair<Collider*, Collider*>, CollisionInfo>>& collisionList)
{

	if (colliders.size() > 1)
	{
		float timeOfContact;
		glm::vec3 n1, n2;
		for (int i = 0; i < colliders.size(); i++)
		{
			for (int a = i + 1; a < colliders.size(); a++)
			{
				if (colliders[i]->testIntersection(colliders[a], dt, timeOfContact, n1, n2));
				collisionList.insert({ timeOfContact, std::make_pair(std::make_pair(colliders[i], colliders[a]), CollisionInfo{ n1, n2, timeOfContact }) });
			}
		}
	}
	else if (colliders.size() == 1)
		return;
	else
	{
		if (first.get()->aabb.testIntersection(second.get()->aabb));
		first.get()->testIntersection(*second.get(), dt, collisionList);

		first.get()->selfIntersection(dt, collisionList);
		second.get()->selfIntersection(dt, collisionList);
	}
}

void BSP::testIntersection(Collider* _collider, float dt, std::map<float, std::pair<std::pair<Collider*, Collider*>, CollisionInfo>>& collisionList)
{
	if (colliders.size() != 0)
	{
		float timeOfContact;
		glm::vec3 n1, n2;
		for (int i = 0; i < colliders.size(); i++)
		{
			if (_collider->testIntersection(colliders[i], dt, timeOfContact, n1, n2))
				collisionList.insert({ timeOfContact, std::make_pair(std::make_pair(_collider, colliders[i]), CollisionInfo{n1, n2, timeOfContact})});
		}
	}
	else if (aabb.testIntersection(_collider->getAABB()))
	{
		first.get()->testIntersection(_collider, dt, collisionList);
		second.get()->testIntersection(_collider, dt, collisionList);
	}
}

void BSP::testIntersection(BSP& bsp, float dt, std::map<float, std::pair<std::pair<Collider*, Collider*>, CollisionInfo>>& collisionList)
{
	glm::vec3 n1, n2;
	float timeOfContact;
	if (colliders.size() != 0)
		if (bsp.colliders.size() != 0)
		{
			for (int i = 0; i < colliders.size(); i++)
			{
				for (int a = 0; a < bsp.colliders.size(); a++)
				{
					if (colliders[i]->testIntersection(bsp.colliders[a], dt, timeOfContact, n1, n2));
					collisionList.insert({ timeOfContact, std::make_pair(std::make_pair(colliders[i], bsp.colliders[a]), CollisionInfo{ n1, n2, timeOfContact }) });
				}
			}
		}
		else
		{
			if (aabb.testIntersection(bsp.aabb))
			{
				testIntersection(*bsp.first.get(), dt,  collisionList);
				testIntersection(*bsp.second.get(), dt, collisionList);
			}
		}
	else if (bsp.colliders.size() != 0)
	{
		if (aabb.testIntersection(bsp.aabb))
		{
			bsp.testIntersection(*first.get(), dt, collisionList);
			bsp.testIntersection(*second.get(), dt, collisionList);
		}
	}
	else {
		first.get()->testIntersection(*bsp.first.get(),dt, collisionList);
		first.get()->testIntersection(*bsp.second.get(),dt,  collisionList);
		second.get()->testIntersection(*bsp.first.get(),dt,  collisionList);
		second.get()->testIntersection(*bsp.second.get(),dt, collisionList);
	}
}
