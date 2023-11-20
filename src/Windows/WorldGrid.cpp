#include "WorldGrid.h"
#include "DynamicCollider.h"

void WorldGrid::updateCollisionList()
{
	std::vector<std::pair<Collider*, Collider*>> emptyVec;
	collisionList.swap(emptyVec);
	for (auto itX = worldGrid.begin(); itX != worldGrid.end(); itX++)
	{
		for (auto itY = worldGrid.at(itX->first).begin(); itY != worldGrid.at(itX->first).end(); itY++)
		{
			for (auto itZ = worldGrid.at(itX->first).at(itY->first).begin(); itZ != worldGrid.at(itX->first).at(itY->first).end(); itZ++)
			{
				if (itZ->second.size() > 1)
					for (int i = 0; i < itZ->second.size(); i++)
					{
						for (int a = i + 1; a < itZ->second.size(); a++)
						{
							if (itZ->second[i]->testIntersection(itZ->second[a]))
								collisionList.push_back(std::make_pair(itZ->second[i], itZ->second[a]));
						}
					}
			}
		}
	}
}

void WorldGrid::updateCollisionList2()
{
	std::vector<std::pair<Collider*, Collider*>> emptyVec;
	collisionList.swap(emptyVec);

	std::vector<Collider*> emptyVec2;
	colliderList.swap(emptyVec2);

	auto entityTypes = ArchetypeList::getArchetypesWith<DynamicCollider>().get();
	for (auto entityType : entityTypes)
	{
		auto entities = Entity::getEntityList(entityType.first);
		for (auto& entity : *entities)
		{
			DynamicCollider* collider = (DynamicCollider*)entity.second.at(DynamicCollider::typeId()).get();
			collider->updateCollider();
			colliderList.push_back(collider);
		}
	}

	for (int i = 0; i < colliderList.size(); i++)
	{
		for (int a = i + 1; a < colliderList.size(); a++)
		{
			if (colliderList[i]->testIntersection(colliderList[a]))
				collisionList.push_back(std::make_pair(colliderList[i], colliderList[a]));
		}
	}
}
