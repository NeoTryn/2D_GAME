#include "ResourceManager.hpp"

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
		}
		catch(std::runtime_error e) {
			std::cerr << e.what() << std::endl;
		}
	}
