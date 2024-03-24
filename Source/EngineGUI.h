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

/*
  Use the imgui to achieve in opengl window to chage opengl render and engine function value
*/
#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif
#include<functional>

// initialize imgui by GLFWwindow object
// window : A OpenGL window object
void initImgui(GLFWwindow* window);

// Create a Frame in OpenGL window
// x        : X Position
// y        : Y Position
// width    : The Frame width
// height   : The Frame height
// callback : give a lambda function and use Imgui function to set the Frame styles in OpenGL window
void createFrame(float x,float y,float width,float height, std::function<void()> const& callback);