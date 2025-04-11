#pragma once
#include<iostream>
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void ShowMouse(GLFWwindow* window);

void setFullScreen(GLFWwindow* window, int key, int action);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void cursor_callback(GLFWwindow* window, double xpos, double ypos);

float deltaTime();

void processKeyboard(GLFWwindow* window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

