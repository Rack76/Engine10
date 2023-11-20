#ifndef DEBUG_CAMERA_H
#define DEBUG_CAMERA_H

#include "PlayerControlledCamera.h"

class DebugCamera : public PlayerControlledCamera
{
public:
	DebugCamera(EntityId id) : PlayerControlledCamera(id)
	
	{

	}
   
	void setUniformTranslation();
	void setUniformRotation(float mouseMotionX, float mouseMotionY);

private:
};

#endif