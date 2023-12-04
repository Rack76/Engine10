#ifndef WORLD_GRID_H
#define WORLD_GRID_H

#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"
#include "Entity.h"
#include "AABB.h"
#include "NameAllocator.h"
#include "RigidBody.h"
#include "Collider.h"
#include <map>
#include <unordered_map>

namespace std {
	template <>
	class hash <glm::vec3> {
		NameAllocator nameAllocator;
	public:
		size_t operator()(const glm::vec3& x)
		{
			return  nameAllocator.getName();
		}
	};
}

struct pairhash {
public:
	std::size_t operator()(const std::pair<glm::vec3, int>& x)
	{
		return std::hash<int>()(x.second);
	}
};

class WorldGrid
{
public:

	template <typename ...Types>
	void findIntersectingCellsWith(std::map<unsigned long, unsigned long> entityTypes)
	{
		if (entityIndicesByComponentType.find(myOr<Types...>()) != entityIndicesByComponentType.end())
		{
			for (auto &entityIndex : entityIndicesByComponentType.at(myOr<Types...>()))
			{
				worldGrid[entityIndex.second.first.x][entityIndex.second.first.y][entityIndex.second.first.z].erase(entityIndex.second.second);
			}
		}

		for (auto entityType : entityTypes)
		{
			auto entities = Entity::getEntityList(entityType.first);
			for (auto& entity : *entities)
			{
				Collider* sCollider = (Collider*)entity.second.at(Collider::typeId()).get();
				sCollider->updateCollider();
				AABB aabb = sCollider->getAABB();
				int xMin = floor(aabb.p1.x / cellWidth);
				int yMin = floor(aabb.p1.y / cellHeight);
				int zMin = floor(aabb.p1.z / cellDepth);

				int xMax = ceil(aabb.p2.x / cellWidth);
				int yMax = ceil(aabb.p2.y / cellHeight);
				int zMax = ceil(aabb.p2.z / cellDepth);

				std::unordered_map<int, std::pair<glm::vec3, int>> emptyMap;
				if (entityIndicesByComponentType.find(myOr<Types...>()) != entityIndicesByComponentType.end())
					entityIndicesByComponentType.at(myOr<Types...>()).swap(emptyMap);

				NameAllocator nameAllocator;

				for (int x = xMin; x < xMax; x++)
				{
					for (int y = yMin; y < yMax; y++)
					{
						for (int z = zMin; z < zMax; z++)
						{
							int a = worldGrid[x][y][z].size();
							entityIndicesByComponentType[myOr<Types...>()].insert({ nameAllocator.getName(), std::make_pair(glm::vec3(x, y, z), worldGrid[x][y][z].size()) });
							worldGrid[x][y][z].insert({ a, sCollider });
						}
					}
				}

			}
		}
	}


	template <typename T>
	void findIntersectingCellsWith()
	{
		if (entityIndicesByComponentType.find(T::typeId()) != entityIndicesByComponentType.end())
		{
			for (auto entityIndex : entityIndicesByComponentType.at(T::typeId()))
			{
				worldGrid[entityIndex.second.first.x][entityIndex.second.first.y][entityIndex.second.first.z].erase(entityIndex.second.second);
			}
		}

		auto entityTypes = ArchetypeList::getArchetypesWith<T>().get();
		for (auto entityType : entityTypes)
		{
			auto entities = Entity::getEntityList(entityType.first);
			for (auto& entity : *entities)
			{
				T* sCollider = (T*)entity.second.at(T::typeId()).get();
				sCollider->updateCollider();
				AABB aabb = sCollider->getAABB();
				int xMin = floor(aabb.p1.x / cellWidth);
				int yMin = floor(aabb.p1.y / cellHeight);
				int zMin = floor(aabb.p1.z / cellDepth);

				int xMax = ceil(aabb.p2.x / cellWidth);
				int yMax = ceil(aabb.p2.y / cellHeight);
				int zMax = ceil(aabb.p2.z / cellDepth);

				std::unordered_map<int, std::pair<glm::vec3, int>> emptyMap;
				if (entityIndicesByComponentType.find(T::typeId()) != entityIndicesByComponentType.end())
					entityIndicesByComponentType.at(T::typeId()).swap(emptyMap);

				NameAllocator nameAllocator;
				
				for (int x = xMin; x < xMax; x++)
				{
					for (int y = yMin; y < yMax; y++)
					{
						for (int z = zMin; z < zMax; z++)
						{
							entityIndicesByComponentType[T::typeId()].insert({ nameAllocator.getName(), std::make_pair(glm::vec3(x, y, z), worldGrid[x][y][z].size())});
							worldGrid[x][y][z].insert({ worldGrid[x][y][z].size(), sCollider });
						}
					}
				}

			}
		}
	}

	template <typename ...Types>
	void updateCollisionList2()
	{
		std::map<int, std::pair<Collider*, Collider*>> emptyVec;
		collisionList.swap(emptyVec);
		if (entityIndicesByComponentType.find(myOr<Types...>()) != entityIndicesByComponentType.end())
		{
			for (auto& entityIndex : entityIndicesByComponentType.at(myOr<Types...>()))
			{
				auto& colliderArray = worldGrid[entityIndex.second.first.x][entityIndex.second.first.y][entityIndex.second.first.z];
					if (colliderArray.size() > 1)
						for (int i = 0; i < colliderArray.size(); i++)
						{
							float oldDistance = std::numeric_limits<float>::max();
							for (int a = i + 1; a < colliderArray.size(); a++)
							{
								float distance;
								if(colliderArray.at(i)->testIntersection(colliderArray.at(a), distance))
									if(distance < oldDistance)
										collisionList.insert({ i, std::make_pair(colliderArray.at(i), colliderArray.at(a)) });
								oldDistance = distance;
							}
						}
			}
		}
	}


	void startDebugging();

	void updateCollisionList();
	std::map<int, std::pair<Collider*, Collider*>>& getCollisionList()
	{
		return collisionList;
	}

	void updateCollisionList2();

private:
	template <typename T, typename ...Types>
	static unsigned long myOr()
	{
		if constexpr (sizeof...(Types) == 0)
			return T::typeId();
		else
			return T::typeId() | myOr<Types...>();
	}

	std::vector<Collider*> colliderList;
	std::unordered_map<unsigned long, std::unordered_map<int, std::pair<glm::vec3, int>>> entityIndicesByComponentType;
	std::map<int, std::pair<Collider*, Collider*>> collisionList;
	std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, Collider*>>>> worldGrid;
	float cellWidth = 2;
	float cellHeight = 2;
	float cellDepth = 2;
};

#endif 