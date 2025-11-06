#include <glad/glad.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef SHADER_HPP
#define SHADER_HPP

class Shader {
public:
	unsigned int program;

	Shader(const char* vertexShaderSrc, const char* fragmentShaderSrc);
	Shader() = default;

	~Shader() = default;

	void use();

	void uniform1i(int value);
	void uniform1f(float value);
	void uniform1d(double value);
	void uniform1b(bool value);
	void uniform1s(std::string value);
	
	void uniformVec2(std::string name, glm::vec2 value);
	void uniformVec3(std::string name, glm::vec3 value);	
	void uniformVec4(std::string name, glm::vec4 value);

	void uniformMat2(std::string name, glm::mat2 value);
	void uniformMat3(std::string name, glm::mat3 value);
	void uniformMat4(std::string name, glm::mat4 value);

private:

	static void checkShaderStatusAndPrintError(unsigned int shader, long type);
	static void checkProgramStatusAndPrintError(unsigned int program);
};

#endif
