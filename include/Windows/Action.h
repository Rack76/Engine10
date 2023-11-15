#ifndef ACTION_H
#define ACTION_H

#include <map>

using EntityIndex = int;
using EntityType = unsigned long;
using EntityId = std::pair<EntityType, EntityIndex>;

namespace Action
{
	void rotateActiveCamera(void* var) {
		auto var2 = (std::tuple<float, float>*) var;
	}
}

#endif