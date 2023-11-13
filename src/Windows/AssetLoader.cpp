#include "AssetLoader.h"
#include <Parser.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void AssetLoader::loadCollada(std::string filepath)
{
	std::vector<float> meshPositions;
	std::vector<float> texCoord;
	Parser::loadMeshFromFile(filepath, meshPositions,texCoord);

	GLuint positions;
	glGenBuffers(1, &positions);
	glBindBuffer(GL_ARRAY_BUFFER, positions);
	glBufferData(GL_ARRAY_BUFFER, meshPositions.size() * 4, meshPositions.data(), GL_STATIC_DRAW);

	GLuint textureCoords;
	glGenBuffers(1, &textureCoords);
	glBindBuffer(GL_ARRAY_BUFFER, textureCoords);
	glBufferData(GL_ARRAY_BUFFER, texCoord.size() * 4, texCoord.data(), GL_STATIC_DRAW);

	positionVbos.insert({ filepath, positions });
	vertexCounts.insert({ filepath, meshPositions.size() / 3 });
	texCoordVbos.insert({ filepath, textureCoords });
}

void AssetLoader::loadTexture(std::string filepath)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int x, y, n;
	unsigned char* data = stbi_load(filepath.c_str(), &x, &y, &n, 0);

	int format;
	if (n == 3)
		format = GL_RGB8;
	else
		format = GL_RGBA8;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	textureObjects.insert({ filepath, texture });
}


void AssetLoader::loadProgram(std::string vertexShader, std::string fragmentShader)
{
	GLuint program = glCreateProgram();
	loadShaderStage(vertexShader, GL_VERTEX_SHADER);
	loadShaderStage(fragmentShader, GL_FRAGMENT_SHADER);
	glAttachShader(program, shaders.at(vertexShader));
	glAttachShader(program, shaders.at(fragmentShader));
	glLinkProgram(program);
	programs.insert({ std::pair<std::string, std::string>(vertexShader, fragmentShader), program });
}

void AssetLoader::loadShaderStage(std::string shaderPath, GLuint shaderType)
{
	std::string shaderString = Parser::loadFileAsString(shaderPath);
	const char* cShaderString = shaderString.c_str();
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &cShaderString, nullptr);
	compileShaderStage(shader);
	shaders.insert({ shaderPath, shader });
}

void AssetLoader::compileShaderStage(GLuint shader)
{
	GLint length;
	glCompileShader(shader);
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
	if (result == 0)
	{
		GLchar* errorMessage = new GLchar[length + 1];
		glGetShaderInfoLog(shader, 100, nullptr, errorMessage);
		std::cout << errorMessage << std::endl;
	}
}

std::map<std::string, GLuint> AssetLoader::positionVbos = std::map<std::string, GLuint>();

std::map<std::string, int> AssetLoader::vertexCounts = std::map<std::string, int>();

std::map<std::string, GLuint> AssetLoader::texCoordVbos = std::map<std::string, GLuint>();

NameAllocator AssetLoader::nameAllocator = NameAllocator(GL_TEXTURE0);

std::map<std::string, GLuint> AssetLoader::textureObjects = std::map<std::string, GLuint>();

std::map<std::pair<std::string, std::string>, GLuint> AssetLoader::programs = std::map<std::pair<std::string, std::string>, GLuint>();

std::map <std::string, GLuint> AssetLoader::shaders = std::map <std::string, GLuint>();