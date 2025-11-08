#include "Shader.hpp"
#include "Entity.hpp"

#include <unordered_map>
#include <string>
#include <memory>

#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer {
private:

	std::shared_ptr<std::unordered_map<std::string, Shader>> shader;
	std::shared_ptr<std::unordered_map<std::string, Entity>> entities;

public:
	
	Renderer(std::shared_ptr<std::unordered_map<std::string, Shader>> shaders_, std::shared_ptr<std::unordered_map<std::string, Entity>> entities_);
	Renderer() = default;
	~Renderer() = default;

	void draw(std::vector<std::string> entities, std::string shader);
};

#endif
