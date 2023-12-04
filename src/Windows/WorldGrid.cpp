#include "WorldGrid.h"

void WorldGrid::startDebugging()
{
	for (auto itX = worldGrid.begin(); itX != worldGrid.end(); itX++)
	{
		for (auto itY = worldGrid.at(itX->first).begin(); itY != worldGrid.at(itX->first).end(); itY++)
		{
			for (auto itZ = worldGrid.at(itX->first).at(itY->first).begin(); itZ != worldGrid.at(itX->first).at(itY->first).end(); itZ++)
			{
				auto value = itY->first * cellHeight;
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
