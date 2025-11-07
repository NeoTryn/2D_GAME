#include <string>

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

struct Texture {
	
	std::string name;
	int width, height, nrChannels;
	unsigned int texture;
};

#endif

#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity {
public:

	Texture texture;	
};

#endif
