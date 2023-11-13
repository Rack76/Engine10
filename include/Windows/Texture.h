#ifndef TEXTURE_H
#define TEXTURE_H

#include <glew.h>
#include <Component.h>
#include <string>
#include <AssetLoader.h>

class Texture : public Counter<Texture>
{
public:
	void setTexture(std::string filepath) {
		texture = AssetLoader::getTextureObject(filepath);
	}

	GLuint texture;
};

#endif