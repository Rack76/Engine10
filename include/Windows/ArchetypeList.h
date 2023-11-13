#ifndef ARCHETYPE_LIST_H
#define ARCHETYPE_LIST_H

#include <map>
#include "Entity.h"

class ArchetypeList
{
public:

	ArchetypeList()
	{
		archetypeIds.clear();
	}

	ArchetypeList(std::map<unsigned long, unsigned long> _archetypeIds)
	{
		archetypeIds = _archetypeIds;
	}

	template <typename T, typename ...Types>
	static ArchetypeList getArchetypesWith()
	{
		std::map<unsigned long, unsigned long> archetypes;
		if (Entity::getEntityTypesByComponentType().find(T::typeId()) == Entity::getEntityTypesByComponentType().end())
			return ArchetypeList();

		archetypes = Entity::getEntityTypesByComponentType().at(T::typeId());
		if constexpr (sizeof...(Types) == 0)
			return ArchetypeList(archetypes);
		else
		{
			return filterArchetypesWith<Types...>(archetypes);
		}
	}

	template <typename T, typename ...Types>
	static ArchetypeList without()
	{
		std::map<unsigned long, unsigned long> returnValue;
		if (Entity::getEntityTypesByComponentType().find(T::typeId()) == Entity::getEntityTypesByComponentType().end())
			return ArchetypeList();

		for (auto archetype : archetypeIds)
		{
			if (!Entity::getArchetype(archetype.first)->hasComponent<T>())
				returnValue.insert({ archetype.first, archetype.first });
		}

		if constexpr (sizeof...(Types) == 0)
		{
			return ArchetypeList(returnValue);
		}
		else
		{
			return filterArchetypesWith<Types...>(returnValue);
		}
	}

	template <typename T, typename ...Types>
	static ArchetypeList filterArchetypesWith(std::map<unsigned long, unsigned long> archetypes)
	{
		std::map<unsigned long, unsigned long> returnValue;
		if (Entity::getEntityTypesByComponentType().find(T::typeId()) == Entity::getEntityTypesByComponentType().end())
			return ArchetypeList();

		for (auto archetype : archetypes)
		{
			if (Entity::getArchetype(archetype.first)->hasComponent<T>())
				returnValue.insert({ archetype.first, archetype.first });
		}

		if constexpr (sizeof...(Types) == 0)
		{
			return ArchetypeList(returnValue);
		}
		else
		{
			return filterArchetypesWith<Types...>(returnValue);
		}
	}

	static std::map<unsigned long, unsigned long> get() {
		return archetypeIds;
	}

private:
	static std::map<unsigned long, unsigned long> archetypeIds;
};

#endif