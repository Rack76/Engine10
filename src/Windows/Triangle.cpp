#include "Triangle.h"
#include "Sphere.h"

bool Triangle::testIntersection(Shape* shape, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2)
{
    return shape->testIntersection(this, dt, firstTimeOfContact, n1, n2);
}

bool Triangle::testIntersection(Sphere* sphere, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2)
{
	return false;
}

bool Triangle::testIntersection(Triangle* triangle, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2)
{
	return false;
}

void Triangle::collisionResponse(Shape* shape, float dt, const float& timeOfContact, glm::vec3& n, glm::vec3 n2)
{
	shape->collisionResponse(this, dt, timeOfContact, n, n2);
}

void Triangle::collisionResponse(Sphere*, float dt, const float& timeOfContact, glm::vec3& n, glm::vec3 n2)
{
}

void Triangle::collisionResponse(Triangle*, float dt, const float& timeOfContact, glm::vec3& n, glm::vec3 n2)
{
}

AABB Triangle::getAABB() {
	std::vector<glm::vec3> _vertices = vertices;
	float minX = std::numeric_limits<float>::max();
	float minY = std::numeric_limits<float>::max();
	float minZ = std::numeric_limits<float>::max();

	float maxX = -std::numeric_limits<float>::max();
	float maxY = -std::numeric_limits<float>::max();
	float maxZ = -std::numeric_limits<float>::max();

	for (auto vertex : _vertices)
	{
		vertex = vertex + center;
	}

	for (auto vertex : vertices)
	{
		if (vertex.x < minX)
			minX = vertex.x;
		if (vertex.x > maxX)
			maxX = vertex.x;

		if (vertex.y < minY)
			minY = vertex.y;
		if (vertex.y > maxY)
			maxY = vertex.y;

		if (vertex.z < minZ)
			minZ = vertex.z;
		if (vertex.z > maxZ)
			maxZ = vertex.z;
	}

	return AABB(glm::vec3(minX, minY, minZ), glm::vec3(maxX, maxY, maxZ));
}