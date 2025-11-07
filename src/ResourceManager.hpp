#include <string>

namespace ResourceManager {
	
	void readFromFile(std::string path, std::string* result);
	void writeToFile(std::string path, std::string content);
}
