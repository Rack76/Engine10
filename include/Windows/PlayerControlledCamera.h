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
			speedVec = glm::vec3(0.0, 1.0, 0.0) * speed;
		else
			speedVec = glm::vec3(0.0, 1.0, 0.0) * -speed;
	}

	void updateTranslationSpeedZ(bool forward)
	{
		auto transform = Entity::getComponent<Transform>(id);

		if (forward)
			speedVec = glm::normalize(glm::vec3(transform->orientation[2].x, 0, transform->orientation[2].z)) * speed;
		else
			speedVec = glm::normalize(glm::vec3(transform->orientation[2].x, 0, transform->orientation[2].z)) * -speed;
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