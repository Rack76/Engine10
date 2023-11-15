#include <Engine.h>
#include <iostream>


int main()
{
	Engine::init();
	Engine::addRunningSystem(1, Renderer::getInstance());
	AssetLoader::loadCollada("mesh/untitled.dae");
	AssetLoader::loadProgram("shader/basicTexture.vert", "shader/basicTexture.frag");
	AssetLoader::loadTexture("texture/texture1.jpg");

	EntityId camera = Entity::addEntity();
	Entity::addComponent<DebugCamera>(camera);
	PlayerControlledCamera::setActivePlayerControlledCameraOwner(camera);

	EntityId entity1 = Entity::addEntity();
	Entity::addComponent<Mesh>(entity1);
	auto mesh = Entity::getComponent<Mesh>(entity1);
	mesh->setMesh("mesh/untitled.dae");
	mesh->setTexture("mesh/untitled.dae");

	Entity::addComponent<Shader>(entity1);
	auto shader = Entity::getComponent<Shader>(entity1);
	shader->setProgram("shader/basicTexture.vert", "shader/basicTexture.frag");

	Entity::addComponent<Texture>(entity1);
	auto texture = Entity::getComponent<Texture>(entity1);
	texture->setTexture("texture/texture1.jpg");

	Engine::run();
	Engine::terminate();
}