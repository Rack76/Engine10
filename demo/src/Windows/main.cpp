#include <Engine.h>
#include <iostream>


int main()
{
	Engine::init();
	AssetLoader::loadCollada("mesh/untitled.dae");
	AssetLoader::loadCollada("mesh/terrain.dae");
	AssetLoader::loadCollada("mesh/triangle.dae");
	AssetLoader::loadCollada("mesh/sphere3.dae");
	AssetLoader::loadProgram("shader/basicTexture.vert", "shader/basicTexture.frag");
	AssetLoader::loadProgram("shader/basic.vert", "shader/redDebug.frag");
	AssetLoader::loadProgram("shader/basic.vert", "shader/greenDebug.frag");
	AssetLoader::loadTexture("texture/texture1.jpg");
	AssetLoader::loadTexture("texture/metal.jpg");

	EntityId camera = Entity::addEntity();
	Entity::addComponent<DebugCamera>(camera);
	PlayerControlledCamera::setActivePlayerControlledCameraOwner(camera);

	EntityId entity1 = Entity::addEntity();
	auto transform = Entity::getComponent<Transform>(entity1);
	transform->setTranslation(glm::vec3(0.0, 10.0, 0.0));

	Entity::addComponent<Mesh>(entity1);
	auto mesh = Entity::getComponent<Mesh>(entity1);
	mesh->setMesh("mesh/sphere3.dae");
	mesh->setTexture("mesh/sphere3.dae");

	Entity::addComponent<Shader>(entity1);
	auto shader = Entity::getComponent<Shader>(entity1);
	shader->setProgram("shader/basicTexture.vert", "shader/basicTexture.frag");

	Entity::addComponent<Texture>(entity1);
	auto texture = Entity::getComponent<Texture>(entity1);
	texture->setTexture("texture/texture1.jpg");

	Entity::addComponent<Collider>(entity1);
	auto collider = Entity::getComponent<Collider>(entity1);
	collider->setShape(Sphere(glm::vec3(0.0, 10.0, 0.0), 1.0));
	
	Entity::addComponent<RigidBody>(entity1);

	Entity::addComponent<PlayerInput>(entity1);
	auto playerInput = Entity::getComponent<PlayerInput>(entity1);
	playerInput->addAction(KEY_RIGHT, 0, Action::translateX);
	playerInput->addAction(KEY_LEFT, 0, Action::translateNegativeX);
	playerInput->addAction(KEY_UP, 0, Action::translateY);
	playerInput->addAction(KEY_DOWN, 0, Action::translateNegativeY);
	playerInput->addAction(-1, 0, Action::stopObject);

	EntityId entity2 = Entity::addEntity();
	auto transform2 = Entity::getComponent<Transform>(entity2);
	transform2->setTranslation(glm::vec3(0.0, 0.0, 0.0));
	transform2->setScale(6);

	Entity::addComponent<Mesh>(entity2);
	auto mesh2 = Entity::getComponent<Mesh>(entity2);
	mesh2->setMesh("mesh/terrain.dae");
	mesh2->setTexture("mesh/terrain.dae");

	Entity::addComponent<Shader>(entity2);
	auto shader2 = Entity::getComponent<Shader>(entity2);
	shader2->setProgram("shader/basicTexture.vert", "shader/basicTexture.frag");

	Entity::addComponent<Texture>(entity2);
	auto texture2 = Entity::getComponent<Texture>(entity2);
	texture2->setTexture("texture/metal.jpg");

	Terrain::loadTerrainCollider(entity2);

	auto sphere1 = Entity::addEntity();
	auto transform3 = Entity::getComponent<Transform>(sphere1);
	transform3->setTranslation(glm::vec3(-3.0, 0.8, 0.2));

	Entity::addComponent<Mesh>(sphere1);
	auto mesh3 = Entity::getComponent<Mesh>(sphere1);
	mesh3->setMesh("mesh/sphere3.dae");
	mesh3->setTexture("mesh/sphere3.dae");

	Entity::addComponent<Shader>(sphere1);
	auto shader3 = Entity::getComponent<Shader>(sphere1);
	shader3->setProgram("shader/basicTexture.vert", "shader/basicTexture.frag");

	Entity::addComponent<Texture>(sphere1);
	auto texture3 = Entity::getComponent<Texture>(sphere1);
	texture3->setTexture("texture/texture1.jpg");

	Entity::addComponent<Collider>(sphere1);
	auto collider3 = Entity::getComponent<Collider>(sphere1);
	collider3->setShape(Sphere(glm::vec3(-3.0, 0.0, 0.3), 1.0));

	Engine::run();
	Engine::terminate();
}