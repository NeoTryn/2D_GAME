#include "Shader.hpp"
#include "Entity.hpp"

#include <unordered_map>
#include <string>
#include <memory>

#ifndef RENDERER_HPP
#define RENDERER_HPP

#define FRUSTUM_WIDTH 160.0f
#define FRUSTUM_HEIGHT 90.0f

class Renderer {
private:

	std::shared_ptr<std::unordered_map<std::string, Shader>> shaders;
	std::shared_ptr<std::unordered_map<std::string, Entity>> entities;

	Entity* getEntityByName(std::string name);
	Shader* getShaderByName(std::string name);
	
	void update(Shader* s, glm::vec3 color, glm::vec2 currentSize, glm::vec2 scale, glm::vec2 position, float rotate, glm::vec2 axis);

public:
	
	Renderer(std::shared_ptr<std::unordered_map<std::string, Shader>> shaders_, std::shared_ptr<std::unordered_map<std::string, Entity>> entities_);
	Renderer() = default;
	~Renderer() = default;

	void draw(std::vector<std::string> entities, std::string shader);
};

#endif
