#include "ResourceManager.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_map>

ResourceManager::ResourceManager() {
	ResourceManager::entities = std::make_shared<std::unordered_map<std::string, Entity>>();
	ResourceManager::shaders = std::make_shared<std::unordered_map<std::string,Shader>>();
	ResourceManager::atlas = std::make_shared<unsigned int>();
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
