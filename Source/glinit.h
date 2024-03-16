#pragma once
#define GLEW_STATIC
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
GLFWwindow* initGLFW(const char* name, int width, int height);
void setCenter(GLFWwindow* window, int width, int height);
void initGLEW();