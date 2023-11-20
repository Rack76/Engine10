#ifndef WORLD_GRID_H
#define WORLD_GRID_H

#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"
#include "Entity.h"
#include "AABB.h"
#include "StaticCollider.h"
#include "NameAllocator.h"
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

	void startDebugging()
	{
		for (auto itX = worldGrid.begin(); itX != worldGrid.end(); itX++)
		{
			for (auto itY = worldGrid.at(itX->first).begin(); itY != worldGrid.at(itX->first).end(); itY++)
			{
				for (auto itZ = worldGrid.at(itX->first).at(itY->first).begin(); itZ != worldGrid.at(itX->first).at(itY->first).end(); itZ++)
				{
					auto value = itY->first* cellHeight;
					glm::vec3 center = glm::vec3(itX->first * cellWidth, value, itZ->first * cellDepth) +
						glm::vec3(cellWidth, cellHeight, cellDepth) * 0.5f;

						auto cellId = Entity::addEntity();
						auto transform = Entity::getComponent<Transform>(cellId);
						transform->setTranslation(center);
						transform->setScale(glm::vec3(cellWidth, cellHeight, cellDepth) * 0.5f);
						Entity::addComponent<Mesh>(cellId);
						auto mesh = Entity::getComponent<Mesh>(cellId);
						mesh->setMesh("mesh/untitled.dae");

						Entity::addComponent<Shader>(cellId);
						auto shader = Entity::getComponent<Shader>(cellId);
						shader->setProgram("shader/basic.vert", "shader/redDebug.frag");
				}
			}
		}
	}

	void updateCollisionList();
	std::vector<std::pair<Collider*, Collider*>>& getCollisionList()
	{
		return collisionList;
	}

	void updateCollisionList2();

private:
	std::vector<Collider*> colliderList;
	std::unordered_map<unsigned long, std::unordered_map<int, std::pair<glm::vec3, int>>> entityIndicesByComponentType;
	std::vector<std::pair<Collider*, Collider*>> collisionList;
	std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, Collider*>>>> worldGrid;
	float cellWidth = 2;
	float cellHeight = 2;
	float cellDepth = 2;
};

#endif 