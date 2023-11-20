#ifndef GET_AABB_BEHAVIOR_H
#define GET_AABB_BEHAVIOR_H

#include "Shape.h"
#include "AABB.h"

//template <typename T>
class GetAABBBehavior
{
public:
	virtual AABB getAABB(Shape*) = 0;
};

#endif 