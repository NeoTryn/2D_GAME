#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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
"	fragCol = vec4(0.9f, 0.3f, 0.5f, 1.0f);\n"
"}\n";

const float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f
};

int main() {

	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!glfwInit()) {
		std::cout << "GLFW failed to initialize.\n";
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "GAME", nullptr, nullptr);

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

	glViewport(0, 0, 800, 600);

	glClearColor(0.3f, 0.5f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	unsigned int vertexShader, fragmentShader;

	char infoLog[512];
	int success;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
	glCompileShader(vertexShader);
	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "Vertex Shader compilation failed. Infolog: " << infoLog << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
	glCompileShader(fragmentShader);
		
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "Fragment Shader compilation failed. Infolog: " << infoLog << std::endl;
	}

	while(!glfwWindowShouldClose(window)) {
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	glfwDestroyWindow(window);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
