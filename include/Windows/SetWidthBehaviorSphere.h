#ifndef SET_WIDTH_BEHAVIOR_SPHERE_H
#define SET_WIDTH_BEHAVIOR_SPHERE_H

#include "SetWidthBehavior.h"
#include "Sphere.h"

class SetWidthBehaviorSphere : public SetWidthBehavior
{
	void setWidth(Shape* shape, float width)
	{
		((Sphere*)shape)->radius = width;
	}
};

#endif 