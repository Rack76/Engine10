#include "Component.h"

unsigned long Count::count = 0;

std::map<unsigned long, std::function<std::unique_ptr<Component>(EntityId)>> Component::componentConstructors =
std::map<unsigned long, std::function<std::unique_ptr<Component>(EntityId)>>();