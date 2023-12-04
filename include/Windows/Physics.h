#ifndef PHYSICS_H
#define PHYSICS_H

#include "Singleton.h"
#include "System.h"
#include "WorldGrid.h"
#include "BSP.h"

class Physics : public Singleton<Physics>, public System
{
public:
	void init();
	void run(float dt);
	void terminate();

private:
	void respondToCollisions(float dt);
	void moveRigidBodies(float dt);
	void buildWorldBSP(BSP& bsp, std::vector<Collider*> colliders);
	void buildWorldStaticBsp();
	void buildWorldDynamicBsp();
	void testIntersectionDynamicStatic(float dt);
	void applyGravity(float dt);
	std::map<float, std::pair<std::pair<Collider*, Collider*>, CollisionInfo>> collisionList;
	WorldGrid grid;
	BSP staticBsp;
	BSP dynamicBsp;
};

#endif 