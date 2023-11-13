#include "Renderer.h"
#include "Entity.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "ArchetypeList.h"

void Renderer::init()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
}



void Renderer::run()
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawTexturedObjects();
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

			Shader* shader = (Shader*)components.at(Shader::typeId()).get();
			glUseProgram(shader->getProgram());

			Texture* texture = (Texture*)components.at(Texture::typeId()).get();
			glBindTexture(GL_TEXTURE_2D, texture->texture);

			glDrawArrays(GL_TRIANGLES, 0, mesh->vertexCount);
		}
	}
}

void Renderer::terminate()
{
}
