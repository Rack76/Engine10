#ifndef ACTION_H
#define ACTION_H

#include <map>

using EntityIndex = int;
using EntityType = unsigned long;
using EntityId = std::pair<EntityType, EntityIndex>;

#include "Entity.h"
#include "Transform.h"

namespace Action
{
	static void translateObjectX(void* var) {
		Transform* transform = (Transform*)var;
		transform->setTranslation(transform->translation + glm::vec3(-0.02, 0.0, 0.0));
	}
}

#endif