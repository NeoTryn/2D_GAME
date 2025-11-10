#include "Game.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

Game::Game(std::string windowName) {
	
	if (!glfwInit()) {
		std::cerr << "GLFW failed to initialize.\n";
		std::exit(EXIT_FAILURE);
	}
	
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	Game::window = glfwCreateWindow(mode->width, mode->height, windowName.c_str(), glfwGetPrimaryMonitor(), nullptr);

	if (!window) {
		std::cerr << "GLFW failed to create a window.\n";
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(Game::window);
	glfwSetFramebufferSizeCallback(Game::window, Game::framebufferSizeCallback);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cerr << "Failed to initialize glad.\n";
		Game::destroy();
		std::exit(EXIT_FAILURE);
	}

	glViewport(0, 0, mode->width, mode->height);
	
	std::string vertexShaderStr, fragmentShaderStr;

	ResourceManager::readFromFile("src/shader/vertex_shader.glsl", &vertexShaderStr);
	ResourceManager::readFromFile("src/shader/fragment_shader.glsl", &fragmentShaderStr);
	
	const char* vertexShaderSrc = vertexShaderStr.c_str();
	const char* fragmentShaderSrc = fragmentShaderStr.c_str();

	Game::mng = {vertexShaderSrc, fragmentShaderSrc};
	
	Game::renderer = {Game::mng.shaders, Game::mng.entities};
}

void Game::loop() {

	while(!glfwWindowShouldClose(Game::window)) {
	
		Game::processInput(Game::window);

		Game::clear();
		Game::render();
		Game::update();
	}
}

void Game::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::render() {
	std::vector<std::string> entities;
	
	entities.push_back("player");

	Game::renderer.draw(entities, "default");
}

void Game::update() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Game::destroy() {
	glfwDestroyWindow(Game::window);
	glfwTerminate();
}

inline void Game::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

inline void Game::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
