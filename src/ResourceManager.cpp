#include "ResourceManager.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "stb_image.h"

ResourceManager::ResourceManager(const char* vertexShaderSrc, const char* fragmentShaderSrc) {
	ResourceManager::entities = std::make_shared<std::unordered_map<std::string, Entity>>();

	Shader shader = {vertexShaderSrc, fragmentShaderSrc};

	ResourceManager::shaders = std::make_shared<std::unordered_map<std::string,Shader>>(std::unordered_map<std::string, Shader>{
				{"default", shader}
			}
		);

	ResourceManager::loadAtlas();
}

void ResourceManager::readFromFile(std::string path, std::string* result) {

	std::ifstream file(path);
		
	std::string line;
		
	try {

		if(!file.good()) {

			std::string message = "The file " + path + " was not found.\n";

			throw std::runtime_error(message);	
		}
		while(std::getline(file, line)) {
			*result += (line + "\n");
		}

		file.close();
	}
	catch(std::runtime_error e) {
		std::cerr << e.what() << std::endl;
	}
}

void ResourceManager::writeToFile(std::string path, std::string content) {
	
	std::ofstream file(path);

	try {

		if(!file.good()) {

			std::string message = "The file " + path + " was not found.\n";

			throw std::runtime_error(message);	
		}
		else {
			
			file << content;

			file.close();
		}
	}
	catch(std::runtime_error e) {
		std::cerr << e.what() << std::endl;
	}
}

void ResourceManager::loadAtlas() {
	
	stbi_set_flip_vertically_on_load(true);

	unsigned int texture;
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrChannels;
	
	const char* path = "img/squid.png";

	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
			
	//std::cout << width << " " << height << " " << nrChannels <<"\n";
	
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cerr << "Image couldn't be loaded. \n";
	}
	stbi_image_free(data);

	(*shaders)["default"].uniform1i("whistle", 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);


	ResourceManager::atlas.width = width;
	ResourceManager::atlas.height = height;
	ResourceManager::atlas.nrChannels = nrChannels;
	ResourceManager::atlas.texture = texture;
}
