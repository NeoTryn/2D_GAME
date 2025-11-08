#include <memory>
#include <string>
#include <unordered_map>

#include "Entity.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"

#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

class ResourceManager {
public:

	std::shared_ptr<std::unordered_map<std::string, Entity>> entities;
	std::shared_ptr<std::unordered_map<std::string, Shader>> shaders;
	
	struct {

		unsigned int texture;
		int width, height, nrChannels;

	} atlas;

	ResourceManager(const char* vertexShaderSrc, const char* fragmentShaderSrc);
	ResourceManager() = default;
	~ResourceManager() = default;

	void loadAtlas(); 

	static void readFromFile(std::string path, std::string* result);
	static void writeToFile(std::string path, std::string content);

};

#endif
