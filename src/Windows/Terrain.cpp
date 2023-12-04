#include "Terrain.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Transform.h"
#include "Mesh.h"
#include "AssetLoader.h"
#include "Collider.h"
#include "Triangle.h"
#include <string>

void Terrain::loadTerrainCollider(EntityId id)
{
	float scale = Entity::getComponent<Transform>(id)->scale[0][0];
	std::string geometryFilePath = Entity::getComponent<Mesh>(id)->geometry;
	auto geometry = AssetLoader::getGeometry(geometryFilePath);

	for (int i = 0; i < geometry.triangles.size(); i += 3)
	{
		std::vector<glm::vec3> vertices;
		vertices.push_back(geometry.triangles[i]);
		vertices.push_back(geometry.triangles[i+1]);
		vertices.push_back(geometry.triangles[i+2]);

		auto triangle = Entity::addEntity();

		Entity::addComponent<Collider>(triangle);
		auto collider = Entity::getComponent<Collider>(triangle);
		collider->setShape(Triangle(vertices));
		collider->setWidth(scale);
	}
}