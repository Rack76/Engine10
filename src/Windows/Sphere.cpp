#include "Sphere.h"
#include "Triangle.h"
#include "RigidBody.h"
#include <iostream>

bool Sphere::testIntersection(Shape* shape, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2)
{
	return shape->testIntersection(this, dt, firstTimeOfContact, n1, n2);
}

bool Sphere::testIntersection(Sphere* shape, float dt, float& firstTimeOfContact, glm::vec3& n1, glm::vec3& n2)
{
	glm::vec3 v1 = glm::vec3(0.0, 0.0, 0.0), v2 = glm::vec3(0.0, 0.0, 0.0);

	if (Entity::entityHasComponent<RigidBody>(id))
		v1 = Entity::getComponent<RigidBody>(id)->velocity;
	if (Entity::entityHasComponent<RigidBody>(shape->id))
		v2 = Entity::getComponent<RigidBody>(shape->id)->velocity;

	glm::vec3 cp1, cp2;
	float contactTime = 0;
	glm::vec3 normalizedCenterDiff1, normalizedCenterDiff2;
	normalizedCenterDiff1 = glm::normalize(center - shape->center);
	normalizedCenterDiff2 = glm::normalize(shape->center - center);
	cp1 = center + normalizedCenterDiff2 * radius;
	cp2 = shape->center + normalizedCenterDiff1 * shape->radius;
	n1 = cp2 - shape->center;
	n2 = cp1 - center;
	glm::vec3 n = glm::normalize(cp2 - cp1);

	if (glm::dot(dt * (v2 - v1), n) == 0.0)
		return false;

	float deltaT = glm::length(cp1 - cp2) / glm::dot(dt * (v2 - v1), n);

	if (0.0 < abs(deltaT) <= 1.0)
	{
		firstTimeOfContact = deltaT;
		return true;
	}
	else
		return false;
}

bool Sphere::testIntersection(Triangle* triangle, float dt, float &firstTimeOfContact, glm::vec3 &n1, glm::vec3& n2)
{	
	glm::vec3 v1 = glm::vec3(0.0, 0.0, 0.0), v2 = glm::vec3(0.0, 0.0, 0.0);

	if (Entity::entityHasComponent<RigidBody>(id))
		v1 = Entity::getComponent<RigidBody>(id)->velocity;
	if (Entity::entityHasComponent<RigidBody>(triangle->id))
		v2 = Entity::getComponent<RigidBody>(triangle->id)->velocity;

	glm::vec3 cp1, cp2;
	float contactTime = 0;
	closestPoints(triangle, cp1, cp2);
	n1 = triangle->normal;
	n2 = cp1 - center;
	float l =  glm::length(cp2 - cp1);
	glm::vec3 n = glm::normalize(cp2 - cp1);

	if (glm::length(cp2 - cp1) == 0)
	{
		firstTimeOfContact = 0.0;
		return true;
	}

	if (glm::dot((v2 - v1), n) == 0.0)
	{
		std::cout << " f " << std::endl;
		return false;
	}

	float deltaT = glm::length(cp1 - cp2) / glm::dot(dt * (v1 - v2), n);

	if ( -1.0 <= deltaT && deltaT <= 1.0)
	{
		firstTimeOfContact = deltaT;
		std::cout << deltaT << " t " << std::endl;
		return true;
	}
	else
	{
		std::cout << deltaT << " f " << std::endl;
		return false;
	}
}

void Sphere::collisionResponse(Shape* shape, float dt, const float& timeOfContact, glm::vec3& n, glm::vec3 n2)
{
	shape->collisionResponse(this, dt, timeOfContact, n, n2);
}

void Sphere::collisionResponse(Sphere* sphere, float dt, const float& timeOfContact, glm::vec3& n, glm::vec3 n2)
{
	
}

void Sphere::collisionResponse(Triangle* triangle, float dt, const float& timeOfContact, glm::vec3& n, glm::vec3 n2)
{
	glm::vec3 velocity = Entity::getComponent<RigidBody>(id)->velocity;
	glm::vec3 translation = Entity::getComponent<Transform>(id)->translation;
	glm::vec3 passedTrajectory = velocity * dt * timeOfContact;
	center = center + passedTrajectory;
	Entity::getComponent<Transform>(id)->translation = center;
	glm::vec3 right = glm::cross(velocity, glm::vec3(0.0, 1.0, 0.0));
	glm::vec3 remainingTrajectory;
	if (glm::length(right) != 0)
	{
		glm::vec3 direction = glm::cross(n, right);
		remainingTrajectory = velocity * dt - passedTrajectory;
		remainingTrajectory = glm::normalize(direction) * glm::length(remainingTrajectory);
	}
	else if (n.y > 0.5 && velocity.x == 0 && velocity.z ==0)
	{
		remainingTrajectory = glm::vec3(0.0, 0.0, 0.0);
	}
	Entity::getComponent<RigidBody>(id)->velocity = remainingTrajectory / dt;
}

void Sphere::closestPoints(Triangle* triangle, glm::vec3 &cp1, glm::vec3 &cp2)
{
	glm::vec3 a = triangle->vertices[0];
	glm::vec3 b = triangle->vertices[1];
	glm::vec3 c = triangle->vertices[2];

	glm::vec3 q = center;

	float d1 = glm::dot(b - a, a - q);
	float d2 = glm::dot(c - a, b - q);
	float d3 = glm::dot(b - a, b - q);
	float d4 = glm::dot(c - a, a - q);

	float d5 = glm::dot(q - a, b - a);
	float d6 = glm::dot(q - a, c - a);
	float d7 = glm::dot(q - b, a - b);
	float d8 = glm::dot(q - c, a - c);
	float d9 = glm::dot(q - c, b - c);
	float d10 = glm::dot(c - q, b - a);
	float d11 = glm::dot(a - q, c - a);
	float d12 = glm::dot(c - q, c - a);
	float d13 = glm::dot(a - q, b - a);
	float d14 = glm::dot(q - b, c - b);

	if (d5 <= 0 && d6 <= 0) //closest vertex is a 
	{
		cp1 = glm::normalize(a - q) * radius + q;
		cp2 = a;
		return;
	}

	if (d8 <= 0 && d9 <= 0) //closest vertex is c
	{
		cp1 = glm::normalize(c - q) * radius + q;
		cp2 = c;
		return;
	}

	if (d7 <= 0 && d14 <= 0) // closest vertex is b
	{
		cp1 = glm::normalize(b - q) * radius + q;
		cp2 = b;
		return;
	}

	float qab = d1 * d2 - d3 * d4;
	if (qab <= 0 && d5 >= 0 && d7 >= 0) //closest edge is ab
	{
		glm::vec3 edgeNormal = glm::cross(-triangle->normal, glm::normalize(b - a));
		glm::vec3 x = b - a;
		glm::vec3 y = x * (d5/ (d5+d7));
		y += a;
		glm::vec3 closestPoint = a + (b - a) * d5 / (d5 + d7);
		cp1 = glm::normalize(closestPoint - q) * radius + q;
		cp2 = closestPoint;
		return;
	}

	float qca = d10 * d11 - d12 * d13;
	if (qca <= 0 && d8 >= 0 && d6 >= 0) //closest edge is ca
	{
		glm::vec3 edgeNormal = glm::cross(-triangle->normal, glm::normalize(a - c));
		glm::vec3 closestPoint = c + (a - c) * d8 / (d8 + d6);
		cp1 = glm::normalize(closestPoint - q) * radius + q;
		cp2 = closestPoint;
		return;
	}

	float qbc = d7 * d8 - d2 * d10;
	if (qbc <= 0 && d14 >= 0 && d9 >= 0) //closest edge is bc
	{
		glm::vec3 edgeNormal = glm::cross(-triangle->normal, glm::normalize(c - b));
		glm::vec3 closestPoint = b + (c - b) * d14 / (d14 + d9);
		cp1 = glm::normalize(closestPoint - q) * radius + q;
		cp2 = closestPoint;
		return;
	}

	float denom = 1.0f / (qab + qca + qbc);
	float u = qbc * denom;
	float v = qca * denom;
	float w = qab * denom;

	glm::vec3 closestPoint = u * a + v * b + w * c;

	if (qbc > 0 && qca > 0 && qab > 0)
	{
		cp1 = glm::normalize(closestPoint - q) * radius + q;
		cp2 = closestPoint;
		return;
	}
}

void Sphere::separateSphere(glm::vec3& center, const glm::vec3& closestPoint, const glm::vec3& normal, const float& radius)
{
	glm::vec3 d = center - closestPoint;
	/*float b = 2 * glm::dot(-normal, d);
	float c = glm::dot(d, d) - radius * radius;
	float delta = b * b - 4 * c;
	float x = (-b + sqrt(delta)) / 2.0f;
	center =  - normal * x + d + closestPoint;*/

	if (-normal.y < 0.5)
	{
		std::cout << "a";
		//glm::vec3 velocity = Entity::getComponent<RigidBody>(id)->velocity;
		//float a = glm::dot(velocity, velocity);
		glm::vec3 collisionNormal = glm::normalize(glm::vec3(normal.x, 0.0f, normal.z));
		float b = 2 * glm::dot(-collisionNormal, d);
		float c = glm::dot(d, d) - radius * radius;
		float delta = b * b - 4 * c;
		float x = (-b + sqrt(delta)) / 2.0f;
		center = -collisionNormal * x + d + closestPoint;

		//glm::vec3 slidingVector = velocity - normal * glm::dot(velocity, normal);
		//center = center + slidingVector;
	}
	else
		center.y = sqrt(radius * radius - pow((center.x - closestPoint.x), 2) - pow((center.z - closestPoint.z), 2)) + closestPoint.y;

	auto transform = Entity::getComponent<Transform>(id);
	transform->setTranslation(center);
	//Entity::getComponent<RigidBody>(id)->velocity = glm::vec3(0.0, 0.0, 0.0);
}

