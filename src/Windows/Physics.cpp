#include "Physics.h"
#include "DynamicCollider.h"

void Physics::init()
{
	grid.findIntersectingCellsWith<StaticCollider>();
	//grid.startDebugging();
}

void Physics::run()
{
	grid.findIntersectingCellsWith<DynamicCollider>();
	grid.updateCollisionList();
	while (grid.getCollisionList().size() != 0)
	{
		respondToCollisions();
		grid.findIntersectingCellsWith<DynamicCollider>();
		grid.updateCollisionList();
	}
}

void Physics::terminate()
{
}

void Physics::respondToCollisions()
{
	for (auto it = grid.getCollisionList().begin(); it != grid.getCollisionList().end();)
	{
		it->first->collisionResponse(it->second);
		it->second->collisionResponse(it->first);
		it = grid.getCollisionList().erase(it);
	}
}
