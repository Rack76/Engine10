#ifndef NAME_ALLOCATOR_H
#define NAME_ALLOCATOR_H

#include <vector>

class NameAllocator
{
public:

	NameAllocator(int _offset = 0) : firstUnusedName(_offset)
	{

	}

	int getName() {
			if (restoredNames.size() == 0)
				return firstUnusedName++;
			else
			{
				int returnValue = restoredNames.at(restoredNames.size() - 1);
				restoredNames.pop_back();
				return returnValue;
			}
	}

	void giveBackName(int name)
	{
		restoredNames.push_back(name);
	}

private:
	int firstUnusedName = 0;
	std::vector<int> restoredNames;
};

#endif
