#ifndef GET_AABB_BEHAVIOR_SPHERE_H
#define GET_AABB_BEHAVIOR_SPHERE_H

#include "StaticSphereCollider.h"
#include "GetAABBBehavior.h"
#include "Sphere.h"

//template <typename T>
class GetAABBBehaviorSphere : public GetAABBBehavior
{
public:
	AABB getAABB(Shape* shape)
	{
		Sphere* sphere = (Sphere*)(shape);
		return AABB(glm::vec3(sphere->center.x - sphere->radius, sphere->center.y - sphere->radius, sphere->center.z - sphere->radius),
			glm::vec3(sphere->center.x + sphere->radius, sphere->center.y + sphere->radius, sphere->center.z + sphere->radius));
	}
};

#endif