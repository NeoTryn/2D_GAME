#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

#ifndef SHADER_HPP
#define SHADER_HPP

class Shader {
public:
	unsigned int program;

	Shader(const char* vertexShaderSrc, const char* fragmentShaderSrc);
	Shader() = default;

	~Shader() = default;

	void use();

	void deleteProgram();

	void uniform1i(std::string name, int value);
	void uniform1f(std::string name, float value);
	void uniform1d(std::string name, double value);
	void uniform1b(std::string name, bool value);
	
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
