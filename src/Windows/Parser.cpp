#include <Parser.h>
#include <sstream>

void ignoreLinesUntil(std::ifstream& file, std::string stringDelim);
void readLinesUntil(std::ifstream& file, std::string& line, std::string stringDelim);
void ignoreCharactersUntil(std::ifstream& file, char charDelim);
void ignoreCharactersUntil(std::string& line, char charDelim);
void readCharactersUntil(std::string& line, char charDelim);
void readUntil(std::ifstream& file, std::string& line, char charDelim);
std::vector<float> castStringToFloatArray(std::string string);
std::vector<unsigned int> castStringToUnsignedIntArray(std::string string);
unsigned int castStringToUnsignedInt(std::string string);
std::vector<unsigned int> filterIndices(int offset, int maxOffset, std::vector<unsigned int> indices);
std::vector<float> sortArray(std::vector<float> unsortedArray, std::vector<unsigned int> indices, int stride);

std::string Parser::loadFileAsString(std::string filepath)
{
	std::ifstream file(filepath, std::ifstream::binary);
	file.seekg(0, file.end);
	int streamSize = file.tellg();
	char* string = new char[streamSize];
	file.seekg(0, file.beg);
	file.read(string, streamSize);
	std::string returnValue(string);
	returnValue.resize(streamSize);
	delete []string;
	return returnValue.c_str();
}

void Parser::loadMeshFromFile(std::string filepath, std::vector<float> &meshPositions, std::vector<float>& texCoord)
{
	unsigned int maxOffset;
	std::string maxOffsetString;
	std::string meshName;
	std::string unsortedMeshPositionsString;
	std::string unsortedTexCoordString;
	std::vector<float> unsortedTexCoord;
	std::vector<float> unsortedMeshPositions;
	std::string indicesString;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> meshPositionsIndices;
	std::vector<unsigned int> texCoordIndices;
	std::ifstream file(filepath);
	ignoreLinesUntil(file, "<library_geometries>");
	ignoreCharactersUntil(file, '\"');
	readUntil(file, meshName, '\"');
	ignoreCharactersUntil(file, '\n');
	ignoreLinesUntil(file, "<source id=\"" + meshName + "-positions\">");
	ignoreCharactersUntil(file, '>');
	readUntil(file, unsortedMeshPositionsString, '<');
	unsortedMeshPositions = castStringToFloatArray(unsortedMeshPositionsString);
	ignoreCharactersUntil(file, '\n');
	ignoreLinesUntil(file, meshName + "-map-0");
	ignoreCharactersUntil(file, '>');
	readUntil(file, unsortedTexCoordString, '<');
	unsortedTexCoord = castStringToFloatArray(unsortedTexCoordString);
	readLinesUntil(file, maxOffsetString, " set=\"1\"/>");
	ignoreCharactersUntil(maxOffsetString, '#');
	ignoreCharactersUntil(maxOffsetString, '=');
	ignoreCharactersUntil(maxOffsetString, '"');
	readCharactersUntil(maxOffsetString, '"');
	maxOffset = castStringToUnsignedInt(maxOffsetString);
	ignoreCharactersUntil(file, '>');
	readUntil(file, indicesString, '<');
	indices = castStringToUnsignedIntArray(indicesString);
	meshPositionsIndices = filterIndices(0, maxOffset, indices);
	texCoordIndices = filterIndices(2, maxOffset, indices);
	meshPositions = sortArray(unsortedMeshPositions, meshPositionsIndices, 3);
	texCoord = sortArray(unsortedTexCoord, texCoordIndices, 2);
}

void ignoreLinesUntil(std::ifstream &file, std::string stringDelim)
{
	std::string line;
	std::getline(file, line);
	while (line.find(stringDelim, 0) == std::string::npos)
	{
		std::getline(file, line);
	}
	//std::getline(file, line);
}

void readLinesUntil(std::ifstream& file, std::string &line, std::string stringDelim)
{
	while (line.find(stringDelim, 0) == std::string::npos)
	{
		std::getline(file, line);
	}
}

void ignoreCharactersUntil(std::ifstream& file, char charDelim)
{
	file.ignore(std::numeric_limits<std::streamsize>::max(), charDelim);
}

void ignoreCharactersUntil(std::string& line, char charDelim)
{
	std::istringstream iss(line);
	int pos = line.find(charDelim);
	line = line.substr(pos + 1);
}

void readCharactersUntil(std::string &line, char charDelim)
{
	std::istringstream iss(line);
	std::getline(iss, line, charDelim);
}

void readUntil(std::ifstream& file, std::string &line, char charDelim)
{
	std::getline(file, line, charDelim);
}

std::vector<float> castStringToFloatArray(std::string string)
{
	std::vector<float> returnValue;
	std::istringstream iss(string);
	float f;
	while (iss >> f)
		returnValue.push_back(f);
	
	return returnValue;
}

std::vector<unsigned int> castStringToUnsignedIntArray(std::string string)
{
	std::vector<unsigned int> returnValue;
	std::istringstream iss(string);
	unsigned int ui;
	while (iss >> ui)
		returnValue.push_back(ui);

	return returnValue;
}

unsigned int castStringToUnsignedInt(std::string string)
{
	std::istringstream iss(string);
	unsigned int ui;
	iss >> ui;
	return ui;
}

std::vector<unsigned int> filterIndices(int offset, int maxOffset, std::vector<unsigned int> indices)
{
	std::vector<unsigned int> filteredIndices;
	for (int i = 0; i < indices.size(); i+= maxOffset + 1)
	{
		filteredIndices.push_back(indices[i + offset]);
	}
	return filteredIndices;
}

std::vector<float> sortArray(std::vector<float> unsortedArray, std::vector<unsigned int> indices, int stride)
{
	std::vector<float> sortedArray;
	for (int i = 0; i < indices.size(); i++)
	{
		for (int a = 0; a < stride; a++)
		{
			sortedArray.push_back(unsortedArray[indices[i] * stride + a]);
		}
	}
	return sortedArray;
}