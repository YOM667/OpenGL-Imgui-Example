#pragma once

#include "EngineGL.h"
#include "EngineGUI.h"
#include "Shader.h"
#include <iostream>

const int DEFAULT_SCREEN_WIDTH = 1270;
const int DEFAULT_SCREEN_HEIGHT = 800;
static float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};
static unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};
enum Mode {
	DEV,USER,DEBUG
};
class GameEngine
{
private:
	void initEngine();
public:
	GameEngine(Mode mode, ImVec4 backgroundColor = {1.0f,1.0f,1.0f,1.0f}, ImVec4 shapeColor = { 0.2f,0.5f,0.4f,1.0f });
	~GameEngine();
	void render();
	void shutdown();
private:
	ImVec4 backgroundColor;
	ImVec4 shapeColor;
	GLFWwindow* window;
	Shader* ourShader;
	Mode mode;
	unsigned int VBO, VAO, EBO;
};

