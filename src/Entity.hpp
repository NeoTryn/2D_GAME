#include <glm/glm.hpp>
#include <vector>

#ifndef ENTITY_HPP
#define ENTITY_HPP


struct AtlasSpec {

	short beginColumn, endColumn, beginRow, endRow, rows, columns;
};

class Entity {
public:

	std::vector<unsigned int> vertexArrayObjects;
	unsigned int elementBufferObject;


	Entity(AtlasSpec spec);

	Entity() = default;
	~Entity() = default;


	inline glm::vec2 getSize() {
		return Entity::modelData.size;
	}

	inline glm::vec2 getScale() {
		return Entity::modelData.scale;
	}

	inline glm::vec2 getPosition() {
		return Entity::modelData.position;
	}

	inline glm::vec2 getAxis() {
		return Entity::modelData.axis;
	}

	inline float getRotation() {
		return Entity::modelData.rotation;
	}

	inline glm::vec3 getColor() {
		return Entity::modelData.color;
	}

	inline void setSize(glm::vec2 size_) {
		Entity::modelData.size = size_;
	}

	inline void setScale(glm::vec2 scale_) {
		Entity::modelData.scale = scale_;
	}

	inline void setPosition(glm::vec2 position_) {
		Entity::modelData.position = position_;
	}

	inline void setRotation(float rotation_) {
		Entity::modelData.rotation = rotation_;
	}

	inline void setAxis(glm::vec2 axis_) {
		Entity::modelData.axis = axis_;
	}

	inline void setColor(glm::vec3 color_) {
		Entity::modelData.color = color_;
	}

private:
	
	struct {

		glm::vec2 size;
		glm::vec2 scale;
		glm::vec2 position;

		glm::vec3 color;
		
		float rotation;
		glm::vec2 axis;

	} modelData;

	void loadSpriteBatch(AtlasSpec spec);
};

#endif
