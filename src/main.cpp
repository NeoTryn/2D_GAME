#include "Game.hpp"
#include <GLFW/glfw3.h>

#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {

	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Game game = {"GAME"};		

	glClearColor(0.3f, 0.5f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	short rows = static_cast<short>(game.mng.atlas.height / 32);
	short columns = static_cast<short>(game.mng.atlas.width / 32);

	std::cout << "Rows: " << rows << "\nColumns: " << columns << std::endl;

	AtlasSpec spec = {0, 1, 0, 1, rows, columns};

	Entity player = {spec};

	(*game.mng.entities)["player"] = player;

	game.loop();	

	game.destroy();

	return 0;
}
