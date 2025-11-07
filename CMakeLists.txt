cmake_minimum_required(VERSION 3.10.0)
project(game VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(game 
               src/main.cpp
               src/glad.c              
               src/stb_image.h
			   src/Shader.cpp
			   src/Shader.hpp
			   src/ResourceManager.hpp
			   src/ResourceManager.cpp
              )

target_include_directories(game PUBLIC ~/include)

target_link_libraries(game 
                      glfw
                      OpenGL::GL    
                      )           
