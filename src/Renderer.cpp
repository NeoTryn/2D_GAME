#include "Renderer.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <iostream>

Renderer::Renderer(std::shared_ptr<std::unordered_map<std::string, Shader>> shaders_, std::shared_ptr<std::unordered_map<std::string, Entity>> entities_) {
	Renderer::shaders = shaders_;
	Renderer::entities = entities_;
}

void Renderer::draw(std::vector<std::string> entities, std::string shader) {
	
	Shader* s = Renderer::getShaderByName(shader);
	
	s->use();

	glm::mat4 projection = glm::mat4(1.0f);

	//projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -100.0f, 100.0f);
	projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

	glm::mat4 view = glm::mat4(1.0f);

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	//projection = glm::rotate(projection, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	s->uniformMat4("proj", projection);
	s->uniformMat4("view", view);

	for (int i = 0; i < entities.size(); i++) {

		//std::cout << entities[i] << std::endl;
		
		Entity* e = Renderer::getEntityByName(entities[i]);
	
		update(s, e->getColor(), e->getSize(), e->getScale(), e->getPosition(), e->getRotation(), e->getAxis());

		s->use();

		glBindVertexArray(e->vertexArrayObjects[0]);

		//std::cout << "VAO " << i << " in Renderer: " << e->vertexArrayObjects[0] << "\n";
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e->elementBufferObject);
		
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void Renderer::update(Shader* s, glm::vec3 color, glm::vec2 currentSize, glm::vec2 scale, glm::vec2 position, float rotate, glm::vec2 axis) {
	
	s->use();

	//std::cout << "Scale.x: "<< scale.x << " Scale.y: " << scale.y << std::endl;

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(0.25f, 0.0f, -3.0f));

	//model = glm::translate(model, glm::vec3(0.5 * currentSize.x, 0.5 * currentSize.y, 0.5f));
	// model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f,1.0f, 1.0f));
	model = glm::rotate(model, static_cast<float>(glfwGetTime()) * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	//model = glm::translate(model, glm::vec3(-0.5 * currentSize.x, -0.5 * currentSize.y, -0.5f));

	model = glm::scale(model, glm::vec3(scale, scale.x));

	s->uniformMat4("model", model);
	s->uniformVec3("color", color);
}

Entity* Renderer::getEntityByName(std::string name) {
	return &((*Renderer::entities).find(name)->second);
}

Shader* Renderer::getShaderByName(std::string name) {
	return &((*Renderer::shaders).find(name)->second);
}
