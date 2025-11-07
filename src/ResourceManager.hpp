#include <memory>
#include <string>
#include <unordered_map>

#include "Entity.hpp"
#include "Shader.hpp"

#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

class ResourceManager {
public:

	std::shared_ptr<std::unordered_map<std::string, Entity>> entities;
	std::shared_ptr<std::unordered_map<std::string, Shader>> shaders;

	ResourceManager();
	~ResourceManager() = default;

	static void readFromFile(std::string path, std::string* result);
	static void writeToFile(std::string path, std::string content);
};

#endif
