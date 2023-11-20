#include <Engine.h>
#include <iostream>


int main()
{
	Engine::init();
	AssetLoader::loadCollada("mesh/untitled.dae");
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
	transform->setTranslation(glm::vec3(0.0, 0.0, 0.5));

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

	Entity::addComponent<StaticCollider>(entity1);

	EntityId entity2 = Entity::addEntity();
	auto transform2 = Entity::getComponent<Transform>(entity2);
	transform2->setTranslation(glm::vec3(2.5, 0.0, 0.0));

	Entity::addComponent<Mesh>(entity2);
	auto mesh2 = Entity::getComponent<Mesh>(entity2);
	mesh2->setMesh("mesh/sphere3.dae");
	mesh2->setTexture("mesh/sphere3.dae");

	Entity::addComponent<Shader>(entity2);
	auto shader2 = Entity::getComponent<Shader>(entity2);
	shader2->setProgram("shader/basicTexture.vert", "shader/basicTexture.frag");

	Entity::addComponent<Texture>(entity2);
	auto texture2 = Entity::getComponent<Texture>(entity2);
	texture2->setTexture("texture/texture1.jpg");

	Entity::addComponent<DynamicCollider>(entity2);

	Entity::addComponent<PlayerInput>(entity2);
	auto playerInput2 = Entity::getComponent<PlayerInput>(entity2);
	playerInput2->addAction(KEY_D, 0, Action::translateObjectX);

	Engine::run();
	Engine::terminate();
}