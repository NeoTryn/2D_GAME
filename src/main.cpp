#include "Shader.hpp"
#include <GLFW/glfw3.h>

#include "ResourceManager.hpp"

#include "stb_image.h"

#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

/*
const char* vertexShaderSrc = 
"#version 460 core\n"
"layout (location = 0) in vec3 vertPos;\n"
"\n"
"void main() {\n"
"	gl_Position = vec4(vertPos, 1.0f);\n"
"}\n";

const char* fragmentShaderSrc = 
"#version 460 core\n"
"out vec4 fragCol;\n"
"\n"
"void main() {\n"
"	fragCol = vec4(0.9, 0.3, 0.5, 1.0);\n"
"}\n";*/

const float vertices[] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f 
};

const int indices[] = {
	0, 1, 3,
	3, 2, 0 
};

int main() {

	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!glfwInit()) {
		std::cout << "GLFW failed to initialize.\n";
		return -1;
	}
	
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "GAME", glfwGetPrimaryMonitor(), nullptr);

	if (!window) {
		std::cout << "GLFW failed to create a window.\n";
		glfwTerminate();
		return -1;
	}

	glfwSetFramebufferSizeCallback(window,framebufferSizeCallback);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cout << "GLAD failed to initialize.\n";
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, mode->width, mode->height);

	glClearColor(0.3f, 0.5f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	std::string vertexShaderStr, fragmentShaderStr;

	ResourceManager::readFromFile("src/shader/vertex_shader.glsl", &vertexShaderStr);
	ResourceManager::readFromFile("src/shader/fragment_shader.glsl", &fragmentShaderStr);
	
	const char* vertexShaderSrc = vertexShaderStr.c_str();
	const char* fragmentShaderSrc = fragmentShaderStr.c_str();

	Shader shader = {vertexShaderSrc, fragmentShaderSrc};	

	shader.use();

	unsigned int VBO, VAO, EBO;

	glCreateBuffers(1, &VBO);
	glCreateBuffers(1, &VAO);
	glCreateBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	stbi_set_flip_vertically_on_load(true);

	unsigned int texture;
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrChannels;
	
	const char* path = "img/squid.png";

	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
			
	std::cout << width << " " << height << " " << nrChannels <<"\n";

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cerr << "Image couldn't be loaded. \n";
	}
	stbi_image_free(data);
	shader.uniform1i("whistle", 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	while(!glfwWindowShouldClose(window)) {
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);
		
		shader.use();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	shader.deleteProgram();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
