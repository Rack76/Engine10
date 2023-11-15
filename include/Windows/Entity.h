#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <tuple>
#include "Archetype.h"
#include "Component.h"
#include "ArchetypeList.h"

using EntityIndex = int;
using EntityType = unsigned long;
using EntityId = std::pair<EntityType, EntityIndex>;

class Entity
{
public:
	static EntityId addEntity();
	static void removeEntity(EntityId id);

	template <typename T>
	static bool entityHasComponent(EntityId id)
	{
		if (archetypesByEntityType.find(id.first) == archetypesByEntityType.end())
		{
			throw std::exception("entity type doesnt exist!");
			return false;
		}

		if (archetypesByEntityType.at(id.first).hasEntity(id.second))
			return archetypesByEntityType.at(id.first).entityHasComponent<T>(id.second);
	}

	template <typename T>
	static void addComponent(EntityId &id)
	{
		unsigned long newEntityType = id.first | T::typeId();
		int newEntityIndex = archetypesByEntityType[newEntityType].addComponent<T>(newEntityType);
		archetypesByEntityType[id.first].transferEntityComponents(newEntityType, id.second,newEntityIndex , &archetypesByEntityType[newEntityType]);
		incrementEntityTypesByComponentTypeArray(newEntityType);
		removeEntity(id);
		id = std::make_pair(newEntityType, newEntityIndex);
	}

	static std::map<int, std::map<unsigned long, std::unique_ptr<Component>>>* getEntityList(unsigned long archetype)
	{
		if (archetypesByEntityType.find(archetype) == archetypesByEntityType.end())
			return nullptr;
		return archetypesByEntityType.at(archetype).getArray();
	}

	template <typename T>
	static T* getComponent(EntityId id)
	{
		return archetypesByEntityType.at(id.first).getComponent<T>(id.second);
	}

	static Archetype* getArchetype(unsigned long entityType)
	{
		return &archetypesByEntityType.at(entityType);
	}

	static std::map<unsigned long, std::map<unsigned long, unsigned long>>& getEntityTypesByComponentType()
	{
		return entityTypesByComponentType;
	}

private:

	static void incrementEntityTypesByComponentTypeArray(unsigned long entityType);
	static void decrementEntityTypesByComponentTypeArray(unsigned long entityType);

	template <typename T>
	static bool hasValue(std::map<T, T>& vec, T value)
	{
		for (std::pair<T, T> element : vec)
		{
			if (element.first == value)
				return true;
		}

		return false;
	}

	static int addEntity(unsigned long entityType);

	template <typename T, typename ...Types>
	static unsigned long myOr()
	{
		if constexpr (sizeof...(Types) == 0)
			return T::typeId();
		else
			return T::typeId() | myOr<Types...>();
	}

	static std::map<unsigned long, Archetype> archetypesByEntityType;
	static std::map<unsigned long, std::map<unsigned long, unsigned long>> entityTypesByComponentType;
};

#endif