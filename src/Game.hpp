#include "ResourceManager.hpp"

#include <GLFW/glfw3.h>

#ifndef GAME_HPP
#define GAME_HPP

class Game {
public:

	GLFWwindow* window;
	ResourceManager mng;
	Renderer renderer;	

	Game(std::string windowName);
	Game() = default;
	~Game() = default;
		
	void loop();

	void update();
	void render();
	void clear();

	void destroy();

private:

	static inline void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static inline void processInput(GLFWwindow* window);
};

#endif
