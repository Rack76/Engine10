#ifndef BSP_H
#define BSP_H

#include "Collider.h"
#include <memory>
#include <vector>
#include "AABB.h"
#include "CollisionInfo.h"

class BSP
{
public:
	void selfIntersection(float dt, std::map<float, std::pair<std::pair<Collider*, Collider*>, CollisionInfo>>& collisionList);
    void testIntersection(Collider*, float dt, std::map<float, std::pair<std::pair<Collider*, Collider*>, CollisionInfo>>& collisionList);

	std::unique_ptr<BSP> first;
	std::unique_ptr<BSP> second;
	std::vector<Collider*> colliders;
	AABB aabb;

	~BSP()
	{
		first.reset();
		second.reset();
		std::vector<Collider*> emptyVec;
		colliders.swap(emptyVec);
	}

private:
	void testIntersection(BSP &bsp, float dt, std::map<float, std::pair<std::pair<Collider*, Collider*>, CollisionInfo>>& collisionList);
};

#endif