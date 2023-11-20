#ifndef PLAYER_CONTROLLED_CAMERA_H
#define PLAYER_CONTROLLED_CAMERA_H

#include <glew.h>
#include <glm/glm.hpp>
#include "Component.h"
#include "Camera.h"
#include "Entity.h"
#include "Transform.h"

class PlayerControlledCamera : public Counter<PlayerControlledCamera>, public Camera
{
public:
	PlayerControlledCamera(EntityId id) : Counter<PlayerControlledCamera>(id), Camera()
	{
		activeCameraOwner = activeCameraOwnerDef;
	}

	void updateTranslationSpeedX(bool forward)
	{
		auto transform = Entity::getComponent<Transform>(id);

		if (forward)
			speedVec = transform->orientation[0] * speed;
		else
			speedVec = transform->orientation[0] * -speed;
	}

	void updateTranslationSpeedY(bool forward)
	{
		auto transform = Entity::getComponent<Transform>(id);

		if (forward)
			speedVec = transform->orientation[1] * speed;
		else
			speedVec = transform->orientation[1] * -speed;
	}

	void updateTranslationSpeedZ(bool forward)
	{
		auto transform = Entity::getComponent<Transform>(id);

		if (forward)
			speedVec = transform->orientation[2] * speed;
		else
			speedVec = transform->orientation[2] * -speed;
	}

	virtual void setUniformRotation(float, float) = 0;
	virtual void setUniformTranslation() = 0;

	static void setActivePlayerControlledCameraOwner(EntityId &id)
	{
		activeCameraOwner = id;
	}

	static EntityId getActivePlayerControlledCameraOwner()
	{
		return activeCameraOwner;
	}

protected:
	static EntityId activeCameraOwnerDef;
	static EntityId &activeCameraOwner;
};

#endif 