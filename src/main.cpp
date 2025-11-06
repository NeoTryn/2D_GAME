#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <iostream>

int main() {

	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!glfwInit()) {
		std::cout << "GLFW failed to initialize.\n";
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "GAME", nullptr, nullptr);
}
