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
#include "Carema.hpp"
#include "Model.h"

#include "Logger.h"
#include "utility.h"

using namespace youm;

const unsigned int DEFAULT_SCREEN_WIDTH = 1270;
const unsigned int DEFAULT_SCREEN_HEIGHT = 800;

#define TITLE "Imgui-OpenGL"

namespace youm::Maple
{
    //glfw events
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow * window, double xPosition, double yPosition);
    static void keyInputCallback(GLFWwindow * window, int key, int scanCode, int action, int mods);
    static void scrollCallback(GLFWwindow * window, double xOffset, double yOffset);

    class GameEngine
    {
    private:
        void initEngine();
        void render();
        void update();
    public:
        enum class Mode {
            DEV, USER, DEBUG
        };
        GameEngine(Mode mode, ImVec4 backgroundColor);
        ~GameEngine();
        void run();
        void shutdown();
    private:
        //engine
        int gameFPS;
        bool gameRunning;
        GLFWwindow* gameWindow;
        //render
        Mode mode;
        unsigned int texture;
        engine::Shader* shader;
        engine::ObjectLoader* objectLoader;
        engine::Model* model;
        ImVec4 backgroundColor;
        static float vertices[];
        unsigned int VBO, VAO;
    };
}
