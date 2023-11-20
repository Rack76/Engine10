#ifndef COMPONENT_H
#define COMPONENT_H

#include <cmath>
#include <map>
#include <functional>
#include <memory>
#include <iostream>

using EntityIndex = int;
using EntityType = unsigned long;
using EntityId = std::pair<EntityType, EntityIndex>;

class Count
{
public:
	static unsigned long count;
};

class Component
{
public:

	Component(EntityId _id) : id(_id)
	{
		
	}

	template <typename T>
	static void registerComponent()
	{
		componentConstructors.insert({ T::typeId(), [](EntityId id) {return std::make_unique<T>(id); } });
	}

	virtual void setEntityId(EntityId _id)
	{
		id = _id;
	}

	EntityId getEntityId()
	{
		return id;
	}

	static std::unique_ptr<Component> getComponent(unsigned long componentTypeId, EntityId id)
	{
		if (componentConstructors.find(componentTypeId) == componentConstructors.end())
		{
			std::cerr << "component not registered !" << std::endl;
			return nullptr;
		}
		return componentConstructors.at(componentTypeId)(id);
	}

	virtual ~Component()
	{
		
	}

protected:
	EntityId id;

private:
	static std::map<unsigned long, std::function<std::unique_ptr<Component>(EntityId)>> componentConstructors;
};

template <typename T> 
class Counter : public Component
{
public:

	Counter(EntityId id) : Component(id)
	{

	}

	static unsigned long typeId()
	{
		static unsigned long TypeId = pow(2, Count::count++);
		return TypeId;
	}

	virtual ~Counter()
	{

	}
};

#endif