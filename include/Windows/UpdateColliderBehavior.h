#ifndef UPDATE_COLLIDER_BEHAVIOR_H
#define UPDATE_COLLIDER_BEHAVIOR_H

#include "Shape.h"
#include "Entity.h"

class UpdateColliderBehavior
{
public:
	virtual void updateCollider(Shape* shape, EntityId) = 0;
};

#endif 