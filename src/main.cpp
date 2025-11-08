#include "ResourceManager.hpp"
#include <GLFW/glfw3.h>

#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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

		ResourceManager mng = {vertexShaderSrc, fragmentShaderSrc};

	

	short rows = static_cast<short>(mng.atlas.height / 32);
	short columns = static_cast<short>(mng.atlas.width / 32);

	std::cout << "Rows: " << rows << "\nColumns: " << columns << std::endl;

	AtlasSpec spec = {0, 1, 0, 1, rows, columns};

	Entity player = {spec};

	(*mng.entities)["player"] = player;

	auto shader = mng.shaders->find("default");

	while(!glfwWindowShouldClose(window)) {
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);
		
		shader->second.use();
		glBindVertexArray(mng.entities->find("player")->second.vertexArrayObjects[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mng.entities->find("player")->second.elementBufferObject);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	shader->second.deleteProgram();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
