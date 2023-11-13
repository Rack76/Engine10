#include "Entity.h"

EntityId Entity::addEntity() {
	int entityIndex = archetypesByEntityType[0].addEntity();
	return std::make_pair(0, entityIndex);
}

void Entity::removeEntity(EntityId id)
{
	archetypesByEntityType.at(id.first).removeEntity(id.second);
	if (archetypesByEntityType.at(id.first).getSize() == 0)
	{
		archetypesByEntityType.erase(id.first);
		decrementEntityTypesByComponentTypeArray(id.first);
	}
}

void Entity::incrementEntityTypesByComponentTypeArray(unsigned long entityType)
{
	if (entityType == 0)
		return;
	else
	{
		int i = entityType;
		while (i > 0)
		{
			unsigned long componentTypeId = pow(2, floor(log2(i)));
			if (!hasValue<unsigned long>(entityTypesByComponentType[componentTypeId], entityType))
				entityTypesByComponentType[componentTypeId].insert({ entityType, entityType });
			i -= componentTypeId;
		}
	}
}

void Entity::decrementEntityTypesByComponentTypeArray(unsigned long entityType)
{
	if (entityType == 0)
		return;
	else
	{
		int i = entityType;
		while (i > 0)
		{
			unsigned long componentTypeId = pow(2, floor(log2(i)));
			if (hasValue<unsigned long>(entityTypesByComponentType[componentTypeId], entityType))
				entityTypesByComponentType[componentTypeId].erase(entityType);
			i -= componentTypeId;
		}
	}
}

int Entity::addEntity(unsigned long entityType)
{
	return archetypesByEntityType[entityType].addEntity();
}

std::map<unsigned long, Archetype> Entity::archetypesByEntityType = std::map<unsigned long, Archetype>();
std::map<unsigned long, std::map<unsigned long, unsigned long>> Entity::entityTypesByComponentType = std::map<unsigned long, std::map<unsigned long, unsigned long>>();