#include <vector>

#ifndef ENTITY_HPP
#define ENTITY_HPP


struct AtlasSpec {

	short beginColumn, endColumn, beginRow, endRow, rows, columns;
};

class Entity {
public:

	std::vector<unsigned int> vertexArrayObjects;
	unsigned int elementBufferObject;

	Entity(AtlasSpec spec);

	Entity() = default;
	~Entity() = default;

private:
	
	void loadSpriteBatch(AtlasSpec spec);
};

#endif
