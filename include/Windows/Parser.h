#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <vector>
#include "glm/gtc/matrix_transform.hpp"

class Parser
{
public:
	static std::string loadFileAsString(std::string filepath);
	static void loadMeshFromFile(std::string filepath, std::vector<float>& meshPositions, std::vector<float>& texCoord, std::vector<glm::vec3>& geometry, std::vector<glm::vec3>& vertices);
};

#endif 