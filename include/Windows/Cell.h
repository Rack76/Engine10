#ifndef CELL_H
#define CELL_H

#include "NameAllocator.h"
#include <functional>

namespace std
{
	template<>
	struct hash<Cell>
	{
		NameAllocator nameAllocator;

		size_t operator()(const Cell &cell)
		{
			return nameAllocator.getName();
		}
	};
}

class Cell
{
	
};

#endif