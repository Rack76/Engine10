#ifndef ASSET_LOADER_H
#define ASSET_LOADER_H

#include <glew.h>
#include <string>
#include <map>
#include <iostream>
#include <NameAllocator.h>

class AssetLoader
{
public:
	static void loadCollada(std::string filepath);

	static void loadTexture(std::string filepath);

	static GLuint getPositionVBO(std::string filepath) {
		try {
			return positionVbos.at(filepath);
		}
		catch (std::exception& e)
		{
			std::cerr << "couldnt find " << filepath << e.what() << std::endl;
		}
	}

	static GLuint getTexCoordVBO(std::string filepath) {
		try {
			return texCoordVbos.at(filepath);
		}
		catch (std::exception& e)
		{
			std::cerr << "couldnt find " << filepath << e.what() << std::endl;
		}
	}

	static int getVertexCount(std::string filepath) {
		try {
			return vertexCounts.at(filepath);
		}
		catch (std::exception& e)
		{
			std::cerr << "couldnt find " << filepath << e.what() << std::endl;
		}
	}

	static GLuint getTextureObject(std::string filepath) {
		try {
			return textureObjects.at(filepath);
		}
		catch (std::exception& e)
		{
			std::cerr << "couldnt find " << filepath << e.what() << std::endl;
		}
	}

	static void loadProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
	static GLuint getProgram(std::string vertexShaderPath, std::string fragmentShaderPath) {
		try {
			return programs.at({ vertexShaderPath, fragmentShaderPath });
		}
		catch (std::exception& e)
		{
			std::cerr << e.what();
		}
	}

private:
	static std::map<std::string, GLuint> texCoordVbos;
	static std::map<std::string, GLuint> positionVbos;
	static std::map<std::string, int> vertexCounts;
	static std::map<std::string, GLuint> textureObjects;
	static void loadShaderStage(std::string shader, GLuint shaderType);
	static void compileShaderStage(GLuint shader);

	static std::map <std::string, GLuint> shaders;
	static std::map<std::pair<std::string, std::string>, GLuint> programs;

	static NameAllocator nameAllocator;
};

#endif