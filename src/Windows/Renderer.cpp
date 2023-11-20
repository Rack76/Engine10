#include "Renderer.h"
#include "Entity.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "DebugCamera.h"
#include <iostream>

void Renderer::init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,  GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
}



void Renderer::run()
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	translatePlayerControlledCamera();
	drawTexturedObjects();
	drawDebugObjects();
	glfwSwapBuffers(window);
}

void Renderer::drawTexturedObjects()
{
	auto archetypeIds = ArchetypeList::getArchetypesWith<Mesh, Shader, Texture>().get();
	for (auto archetypeId : archetypeIds)
	{	
		auto entityList = Entity::getEntityList(archetypeId.first);
		for (auto &entity : *entityList)
		{
			auto& components = entity.second;

			Mesh* mesh = (Mesh*)components.at(Mesh::typeId()).get();
			glBindVertexArray(mesh->vao);

			Transform* transform = (Transform*)components.at(Transform::typeId()).get();

			Shader* shader = (Shader*)components.at(Shader::typeId()).get();
			glUseProgram(shader->getProgram());
			glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "objectTransform"), 1, GL_FALSE, &transform->uniform[0][0]);

			Texture* texture = (Texture*)components.at(Texture::typeId()).get();
			glBindTexture(GL_TEXTURE_2D, texture->texture);

			glDrawArrays(GL_TRIANGLES, 0, mesh->vertexCount);
		}
	}
}

void Renderer::drawDebugObjects()
{
	auto archetypeIds = ArchetypeList::getArchetypesWith<Mesh, Shader>().without<Texture>().get();
	for (auto archetypeId : archetypeIds)
	{
		auto entityList = Entity::getEntityList(archetypeId.first);
		for (auto& entity : *entityList)
		{
			auto& components = entity.second;

			Mesh* mesh = (Mesh*)components.at(Mesh::typeId()).get();
			glBindVertexArray(mesh->vao);

			Transform* transform = (Transform*)components.at(Transform::typeId()).get();

			Shader* shader = (Shader*)components.at(Shader::typeId()).get();
			glUseProgram(shader->getProgram());
			glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "objectTransform"), 1, GL_FALSE, &transform->uniform[0][0]);

			glDrawArrays(GL_TRIANGLES, 0, mesh->vertexCount);
		}
	}
}

void Renderer::translatePlayerControlledCamera()
{
	auto cameraOwner = PlayerControlledCamera::getActivePlayerControlledCameraOwner();
	auto camera = Entity::getComponent<PlayerControlledCamera>(cameraOwner);
	auto transform = Entity::getComponent<Transform>(cameraOwner);
	transform->translation = transform->translation + camera->getSpeedVec();
	camera->setUniformTranslation();
}

void Renderer::terminate()
{
}
