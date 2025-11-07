#include <string>
#include <vector>

#ifndef ENTITY_HPP
#define ENTITY_HPP


struct AtlasSpec {

	short beginColumn, endColumn, beginRow, endRow;
};

class Entity {
public:

	std::vector<unsigned int> vertexArrayObjects;

	Entity(std::string samplerName, AtlasSpec);
	~Entity() = default;

private:
	
	void loadSpriteBatch(AtlasSpec atlasSpec);
	void loadTexture(std::string samplerName);
};

#endif
