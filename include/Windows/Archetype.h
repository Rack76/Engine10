#ifndef ARCHETYPE_H
#define ARCHETYPE_H

#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include "NameAllocator.h"
#include "Component.h"

class Archetype
{
public:

	template <typename T> 
	int addComponent()
	{
		int name = addEntity();
		entities.at(name).insert({ T::typeId(), Component::getComponent(T::typeId())});
		return name;
	}

	void addComponent(int entityIndex, unsigned long componentTypeId, Component* c)
	{
		entities.at(entityIndex).insert({componentTypeId, std::unique_ptr<Component>(c)});
	}

	void transferEntityComponents(int oldEntityIndex, int newEntityIndex, Archetype* destArchetype)
	{
		for (auto it = entities.at(oldEntityIndex).begin(); it != entities.at(oldEntityIndex).end(); it++)
		{
			auto c = it->second.get();
			it->second.release();
			destArchetype->addComponent(newEntityIndex, it->first, c);
		}
	}

	int addEntity()
	{
		int name = nameAllocator.getName();
		entities.insert({ name, std::map<unsigned long, std::unique_ptr<Component>>() });
		//addComponents(name, entityType);
		return name;
	}

	bool hasEntity(int index)
	{
		if (entities.find(index) == entities.end())
		{
			throw std::exception("entity doesnt exist!");
			return false;
		}
		return true;
	}

	template <typename T>
	bool entityHasComponent(int index)
	{
		if (entities.at(index).find(T::typeId()) == entities.at(index).end())
			return false;
		return true;
	}

	template <typename T>
	bool hasComponent()
	{
		return entityHasComponent<T>(0);
	}

	void removeEntity(int index)
	{
		if (index >= entities.size())
		{
			std::cerr << "error : invalid index in Archetype::removeEntity : index = " << index << std::endl;
			return;
		}
		entities.erase(index);
	}

	int getSize() {
		return entities.size();
	}

	std::map<int, std::map<unsigned long, std::unique_ptr<Component>>>* getArray()
	{
		return &entities;
	}

	template <typename T>
	T* getComponent(int index)
	{
		try {
			unsigned long componentType = T::typeId();
			if (entities.at(index).find(componentType) == entities.at(index).end())
			{
				std::cerr << "no such component at entity " << index << std::endl;
				return nullptr;
			}
			else
				return (T*)entities.at(index).at(componentType).get();
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}



private:
	void addComponents(int name, unsigned long entityType)
	{
		if (entityType == 0)
			return;
		else
		{
			unsigned long componentTypeId = pow(2, floor(log2(entityType)));
			entities.at(name).insert({ componentTypeId, Component::getComponent(componentTypeId)});
			if (entities.at(name).at(componentTypeId).get() == nullptr)
			{
				entities.at(name).erase(componentTypeId);
				return;
			}
			entityType -= componentTypeId;
			addComponents(name, entityType);
		}
	}

	std::map<int, std::map<unsigned long, std::unique_ptr<Component>>> entities;

	NameAllocator nameAllocator;
};

#endif