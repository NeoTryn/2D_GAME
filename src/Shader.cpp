#include "Shader.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Shader::Shader(const char* vertexShaderSrc, const char* fragmentShaderSrc) {
	unsigned int vertexShader, fragmentShader;

	char infoLog[512];
	int success;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
	glCompileShader(vertexShader);
	
	Shader::checkShaderStatusAndPrintError(vertexShader, GL_VERTEX_SHADER);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
	glCompileShader(fragmentShader);

	Shader::checkShaderStatusAndPrintError(fragmentShader, GL_FRAGMENT_SHADER);

	Shader::program = glCreateProgram();
	glAttachShader(Shader::program ,vertexShader);
	glAttachShader(Shader::program, fragmentShader);
	glLinkProgram(Shader::program);

	Shader::checkProgramStatusAndPrintError(Shader::program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() {
	glUseProgram(Shader::program);
}

void Shader::deleteProgram() {
	glDeleteProgram(Shader::program);
}

void Shader::checkShaderStatusAndPrintError(unsigned int shader, long type) {
	
	int success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);

		if (type == GL_VERTEX_SHADER) {
			std::cout << "Vertex Shader compilation failed. Infolog: " << infoLog << std::endl;
		}
		else if (type == GL_FRAGMENT_SHADER) {
			std::cout << "Fragment Shader compilation failed. Infolog: " << infoLog << std::endl;
		} 
	}
}

void Shader::checkProgramStatusAndPrintError(unsigned int program) {
	
	int success;
	char infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(program, 512, nullptr, infoLog);

		std::cout << "Shader Program linking failed. Infolog: " << infoLog << std::endl;
	}
}

void Shader::uniform1i(std::string name, int value) {
	const char* nameCStr = name.c_str();

	glUniform1i(glGetUniformLocation(Shader::program, nameCStr), value);
}

void Shader::uniform1f(std::string name, float value) {
	const char* nameCStr = name.c_str();

	glUniform1f(glGetUniformLocation(Shader::program, nameCStr), value);
}

void Shader::uniform1d(std::string name, double value) {
	const char* nameCStr = name.c_str();

	glUniform1d(glGetUniformLocation(Shader::program, nameCStr), value);
}

void Shader::uniform1b(std::string name, bool value) {
	const char* nameCStr = name.c_str();

	glUniform1i(glGetUniformLocation(Shader::program, nameCStr), static_cast<int>(value));
}

void Shader::uniformVec2(std::string name, glm::vec2 value) {
	const char* nameCStr = name.c_str();

	glUniform2fv(glGetUniformLocation(Shader::program, nameCStr), 1, glm::value_ptr(value));
}

void Shader::uniformVec3(std::string name, glm::vec3 value) {
	const char* nameCStr = name.c_str();

	glUniform3fv(glGetUniformLocation(Shader::program, nameCStr), 1, glm::value_ptr(value));
}

void Shader::uniformVec4(std::string name, glm::vec4 value) {
	const char* nameCStr = name.c_str();

	glUniform4fv(glGetUniformLocation(Shader::program, nameCStr), 1, glm::value_ptr(value));
}

void Shader::uniformMat2(std::string name, glm::mat2 value) {
	const char* nameCStr = name.c_str();

	glUniformMatrix2fv(glGetUniformLocation(Shader::program, nameCStr), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::uniformMat3(std::string name, glm::mat3 value) {
	const char* nameCStr = name.c_str();

	glUniformMatrix3fv(glGetUniformLocation(Shader::program, nameCStr), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::uniformMat4(std::string name, glm::mat4 value) {
	const char* nameCStr = name.c_str();

	glUniformMatrix4fv(glGetUniformLocation(Shader::program, nameCStr), 1, GL_FALSE, glm::value_ptr(value));
}
