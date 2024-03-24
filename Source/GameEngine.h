// =========================================================================
// Copyright The YouM, All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// =========================================================================

#pragma once

#include "EngineGL.h"
#include "EngineGUI.h"
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "image/stb_image.h"

#include <iostream>
enum class Mode {
	DEV, USER, DEBUG
};
const int DEFAULT_SCREEN_WIDTH = 1270;
const int DEFAULT_SCREEN_HEIGHT = 800;
static float texCoords[] = {
	0.0f, 0.0f, 
	1.0f, 0.0f, 
	0.5f, 1.0f 
};
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
class GameEngine
{
private:
	void initEngine();
public:

	GameEngine(Mode mode = Mode::USER, ImVec4 backgroundColor = { 1.0,1.0,1.0,1.0 }, ImVec4 shapeColor = { 0.3,0.2,0.4,1.0 });
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