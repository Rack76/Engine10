#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include "Component.h"
#include "AssetLoader.h"

class Mesh : public Counter<Mesh>
{
public:
	Mesh() {
		glGenVertexArrays(1, &vao);
	}

	void setMesh(std::string filepath)
	{
		glBindVertexArray(vao);
		positionVbo = AssetLoader::getPositionVBO(filepath);
		glBindBuffer(GL_ARRAY_BUFFER, positionVbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

		vertexCount = AssetLoader::getVertexCount(filepath);
	}

	void setTexture(std::string filepath)
	{
		glBindVertexArray(vao);
		texCoordVBO = AssetLoader::getTexCoordVBO(filepath);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(1);
	}

	~Mesh() {
		glDeleteVertexArrays(1, &vao);
	}

	GLuint vao;
	int vertexCount;

private:
	GLuint positionVbo;
	GLuint texCoordVBO;
};

#endif 