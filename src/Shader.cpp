#include "Shader.hpp"

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
