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
//defined glew static to init static library
#define GLEW_STATIC


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <windows.h>
#include <iostream>

#include "Carema.hpp"

namespace youm::engine {
    //init glfw to get gameWindow pointer
    //name   : gameWindow's title
    //width  : gameWindow's width
    //height : gameWindow's height
    GLFWwindow* initGLFW(const char* name, int width, int height);
    //set gameWindow in center on your screen
    void setWindowCenter(GLFWwindow* window, int width, int height);
    //init opengl pointer
    void initGLEW();
    //load image
    //file  : the image path name
    //format: opengl color format 'GL_RGB' 'GL_RGBA'
    //slot  : opengl texture slot
    unsigned int loadImage(const char* file, GLint internal_format, GLenum format, int slot);
}

