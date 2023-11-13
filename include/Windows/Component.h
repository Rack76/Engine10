#ifndef COMPONENT_H
#define COMPONENT_H

#include <cmath>
#include <map>
#include <functional>
#include <memory>
#include <iostream>

class Count
{
public:
	static unsigned long count;
};

class Component
{
public:

	template <typename T>
	static void registerComponent()
	{
		componentConstructors.insert({ T::typeId(), []() {return std::make_unique<T>(); } });
	}

	static std::unique_ptr<Component> getComponent(unsigned long componentTypeId)
	{
		if (componentConstructors.find(componentTypeId) == componentConstructors.end())
		{
			std::cerr << "component not registered !" << std::endl;
			return nullptr;
		}
		return componentConstructors.at(componentTypeId)();
	}

private:
	static std::map<unsigned long, std::function<std::unique_ptr<Component>()>> componentConstructors;
};

template <typename T> 
class Counter : public Component
{
public:
	static int typeId()
	{
		static unsigned long TypeId = pow(2, Count::count++);
		return TypeId;
	}
};

#endif