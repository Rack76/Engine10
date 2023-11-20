#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include <functional>
#include <map>
#include "Component.h"

enum Trigger{KEY_A, KEY_D, KEY_Z, KEY_S, KEY_SPACE, KEY_LEFT_SHIFT,
	MOUSE_MOTION};

class PlayerInput : public Counter<PlayerInput>
{
public:

	PlayerInput(EntityId id) : Counter<PlayerInput>(id)
	{
		
	}

	void addAction(int trigger, int order, std::function<void(void*)> action)
	{
			actions[trigger].insert({ order, action });
	}

	void runActions(int trigger, void* data)
	{
		for (auto action : actions.at(trigger))
		{
			action.second(data);
		}
	}

private:
	std::map<int, std::map<int, std::function<void(void*)>>> actions;
};

#endif