#ifndef PLAYER_CONTROLLED_CAMERA_H
#define PLAYER_CONTROLLED_CAMERA_H

#include <glew.h>
#include <glm/glm.hpp>
#include "Component.h"
#include "Camera.h"

class PlayerControlledCamera : public Counter<PlayerControlledCamera>, public Camera
{
public:
	PlayerControlledCamera(EntityId id) : Counter<PlayerControlledCamera>(id), Camera()
	{
		activeCameraOwner = activeCameraOwnerDef;
	}

	virtual void setOrientation(float mouseMotionX, float mouseMotionY) = 0;
	virtual void updateTranslationX(bool forward) = 0;
	virtual void updateTranslationY(bool forward) = 0;
	virtual void updateTranslationZ(bool forward) = 0;

	static void setActivePlayerControlledCameraOwner(EntityId &id)
	{
		activeCameraOwner = id;
	}

	static EntityId getActivePlayerControlledCameraOwner()
	{
		return activeCameraOwner;
	}

protected:
	virtual void rotateCamera(float mouseMotionX, float mouseMotionY) = 0;
	static EntityId activeCameraOwnerDef;
	static EntityId &activeCameraOwner;
};

#endif 