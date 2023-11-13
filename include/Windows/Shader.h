#ifndef SHADER_H
#define SHADER_H

#include <glew.h>
#include "Component.h"
#include "AssetLoader.h"

class Shader : public Counter<Shader>
{
public:
	void setProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
	{
		program = AssetLoader::getProgram(vertexShaderPath, fragmentShaderPath);
	}

	unsigned int getProgram()
	{
		return program;
	}
private:

	GLuint program = 0;
};

#endif 