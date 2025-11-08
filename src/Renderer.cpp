#include "Renderer.hpp"

Renderer::Renderer(std::shared_ptr<std::unordered_map<std::string, Shader>> shaders_, std::shared_ptr<std::unordered_map<std::string, Entity>> entities_) {
	Renderer::shader = shaders_;
	Renderer::entities = entities_;
}

void Renderer::draw(std::vector<std::string> entities, std::string shader) {
	
	for (int i = 0; i < entities.size(); i++) {
		
		Entity e = (*Renderer::entities).find(entities[i])->second;
		Shader s = (*Renderer::shader).find(shader)->second;
		
		glBindVertexArray(e.vertexArrayObjects[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e.elementBufferObject);
		
		s.use();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
