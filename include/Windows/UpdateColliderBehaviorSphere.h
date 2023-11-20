#ifndef UPDATE_COLLIDER_BEHAVIOR_SPHERE_H
#define UPDATE_COLLIDER_BEHAVIOR_SPHERE_H

#include "UpdateColliderBehavior.h"
#include "Transform.h"
#include "Sphere.h"

class UpdateColliderBehaviorSphere : public UpdateColliderBehavior
{
public:
	void updateCollider(Shape* shape, EntityId id)
	{
		Transform* transform = Entity::getComponent<Transform>(id);
		((Sphere*)shape)->center = transform->translation;
	}
};

#endif 