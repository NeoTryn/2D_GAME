#include "Renderer.hpp"

Renderer::Renderer(std::shared_ptr<std::unordered_map<std::string, Shader>> shader_, std::shared_ptr<std::unordered_map<std::string, Entity>> entities_) {
	Renderer::shader = shader_;
	Renderer::entities = entities_;
}


