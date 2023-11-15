#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include <functional>
#include <map>
#include "Component.h"

enum Trigger{KEY, MOUSE_MOTION};

class PlayerInput : public Counter<PlayerInput>
{
public:

	PlayerInput(EntityId id) : Counter<PlayerInput>(id)
	{
		actions[KEY];
		actions[MOUSE_MOTION];
	}

	void addAction(int trigger, int order, std::function<void(void*)> action)
	{
			actions[trigger].insert({ order, action });
	}

private:
	std::map<int, std::map<int, std::function<void(void*)>>> actions;
};

#endif