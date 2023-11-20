#ifndef PHYSICS_H
#define PHYSICS_H

#include "Singleton.h"
#include "System.h"
#include "CollisionDetection.h"

class Physics : public Singleton<Physics>, public System
{
public:
	void init();
	void run();
	void terminate();

private:
	void respondToCollisions();
	WorldGrid grid;
};

#endif 