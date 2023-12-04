#ifndef ACTION_H
#define ACTION_H

#include <map>

#include "Entity.h"
#include "Transform.h"
#include "RigidBody.h"

namespace Action
{
	static void translateX(void*, EntityId id) {
		RigidBody* rigidBody = Entity::getComponent<RigidBody>(id);
		Transform* transform = Entity::getComponent<Transform>(id);
		rigidBody->velocity = transform->orientation[0] * 0.3f;
	}

	static void translateNegativeX(void*, EntityId id) {
		RigidBody* rigidBody = Entity::getComponent<RigidBody>(id);
		Transform* transform = Entity::getComponent<Transform>(id);
		rigidBody->velocity = -transform->orientation[0] * 0.3f;
	}

	static void translateY(void*, EntityId id) {
		RigidBody* rigidBody = Entity::getComponent<RigidBody>(id);
		rigidBody->velocity = glm::vec3(0.0, 0.3, 0.0);
	}

	static void translateNegativeY(void*, EntityId id) {
		RigidBody* rigidBody = Entity::getComponent<RigidBody>(id);
		rigidBody->velocity = glm::vec3(0.0, -0.3, 0.0);
	}

	static void stopObject(void*, EntityId id) {
		RigidBody* rigidBody = Entity::getComponent<RigidBody>(id);
		rigidBody->velocity = glm::vec3(0.0, 0.0, 0.0);
	}
}

#endif