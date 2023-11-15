#include "PlayerControlledCamera.h"

EntityId PlayerControlledCamera::activeCameraOwnerDef = EntityId(-1, -1);
EntityId& PlayerControlledCamera::activeCameraOwner = PlayerControlledCamera::activeCameraOwnerDef;