#ifndef DEBUG_CAMERA_H
#define DEBUG_CAMERA_H

#include "PlayerControlledCamera.h"

class DebugCamera : public PlayerControlledCamera
{
public:
	DebugCamera(EntityId id) : PlayerControlledCamera(id)
	
	{

	}
   
	void setOrientation(float mouseMotionX, float mouseMotionY);

	void updateTranslationX(bool forward);
	void updateTranslationY(bool forward);
	void updateTranslationZ(bool forward);

private:
	void rotateCamera(float mouseMotionX, float mouseMotionY);
};

#endif