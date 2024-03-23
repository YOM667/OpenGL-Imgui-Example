#pragma once
//defined glew static to init static library
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <iostream>
GLFWwindow* initGLFW(const char* name, int width, int height);
void setCenter(GLFWwindow* window, int width, int height);
void initGLEW();