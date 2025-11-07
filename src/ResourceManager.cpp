#include "ResourceManager.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

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
