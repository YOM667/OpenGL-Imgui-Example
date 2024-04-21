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

#include "GameEngine.h"

engine::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// world space positions of our cubes
glm::vec3 cubePositions[10][10][10];

bool mouse         = true;
bool hiddenCursor = false;
float lastX          = DEFAULT_SCREEN_WIDTH / 2.0f;
float lastY          = DEFAULT_SCREEN_HEIGHT / 2.0f;
namespace youm::Maple
{
    float GameEngine::vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };


    void keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            hiddenCursor = !hiddenCursor;
        }
    }

    void framebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new gameWindow dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    void mouseCallback(GLFWwindow* window, double xPosition, double yPosition)
    {
        auto xPos = static_cast<float>(xPosition);
        auto yPos = static_cast<float>(yPosition);

        if (mouse)
        {
            lastX = xPos;
            lastY = yPos;
            mouse = false;
        }

        float xOffset = xPos - lastX;
        float yOffset = lastY - yPos; // reversed since y-coordinates go from bottom to top

        lastX = xPos;
        lastY = yPos;

        camera.ProcessMouseMovement(xOffset, yOffset);
    }

    void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
    {
        camera.ProcessMouseScroll(static_cast<float>(yOffset));
    }


    GameEngine::GameEngine(Mode mode, ImVec4 backgroundColor) : mode(mode), backgroundColor(backgroundColor)
    {
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                for(int k = 0; k < 10; k++)
                {
                    cubePositions[i][j][k] = glm::vec3(i, j, k);
                }
            }
        }
        //Get GLFW gameWindow
        this->gameWindow = engine::initGLFW(TITLE, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
        //on gameWindow size update
        glfwSetFramebufferSizeCallback(this->gameWindow, framebufferSizeCallback);
        //on scroll update
        glfwSetScrollCallback(this->gameWindow, scrollCallback);
        //on input key
        glfwSetKeyCallback(this->gameWindow, keyInputCallback);
        //on cursor position update
        glfwSetCursorPosCallback(this->gameWindow, mouseCallback);
        engine::initImgui(this->gameWindow);
        engine::initGLEW();
        this->objectLoader = new engine::ObjectLoader();
        this->shader = new engine::Shader("Assets/vertex.glsl", "Assets/textures.glsl");
        info("load shader");
        this->initEngine();
        info("init game engine");
    }

    GameEngine::~GameEngine()
    {
        if (this->shader != nullptr)
        {
            delete this->shader;
            this->shader = nullptr;
            info("delete shader");
        }
        if (this->objectLoader != nullptr)
        {
            delete this->objectLoader;
            this->objectLoader = nullptr;
            info("delete object loader");
        }
        if (this->model != nullptr)
        {
            delete this->model;
            this->model = nullptr;
            info("delete object model");
        }
    }

    void GameEngine::initEngine()
    {
        model = objectLoader->loadModel(vertices,sizeof(vertices));
        //load image
        this->texture = engine::loadImage("Assets/container.jpg", GL_RGB, GL_RGB, 0);
    }

    void GameEngine::render()
    {
        glfwPollEvents();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
                                                (float)DEFAULT_SCREEN_WIDTH / (float)DEFAULT_SCREEN_HEIGHT,
                                                0.1f,
                                                100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        if(!hiddenCursor)
        {
            glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        glClearColor(
                this->backgroundColor.x * this->backgroundColor.w,
                this->backgroundColor.y * this->backgroundColor.w,
                this->backgroundColor.z * this->backgroundColor.w,
                this->backgroundColor.w
        );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        this->shader->use();
        this->shader->setMatrix4F("projection", projection);
        this->shader->setMatrix4F("view", view);
        

        objectLoader->bind();
        for (auto & i : cubePositions)
        {
            for (auto & j : i)
            {
                for (auto k : j)
                {
                    // calculate the model matrix for each object and pass it to shader before drawing
                    auto model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                    model = glm::translate(model, k);
                    shader->setMatrix4F("model", model);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
            }
        }
        if (this->mode == Mode::DEV)
        {
            auto callback = [=]()->void {
                ImGui::Text(u8"FPS: %d", gameFPS);
                if (ImGui::TreeNode(u8"摄像机"))
                {
                    ImGui::SliderFloat(u8"摄像机速度", &camera.MovementSpeed, 1.0f, 6.0f);
                    ImGui::TreePop();
                    ImGui::Spacing();
                }
                if (ImGui::TreeNode(u8"渲染"))
                {
                    ImGui::ColorEdit3(u8"背景颜色", (float*)&this->backgroundColor);
                    ImGui::TreePop();
                    ImGui::Spacing();
                }
                if (ImGui::TreeNode(u8"操作"))
                {
                    ImGui::Checkbox(u8"隐藏鼠标", &hiddenCursor);
                    ImGui::TreePop();
                    ImGui::Spacing();
                }
                };
            engine::createFrame(u8"设置", 0, 0, 300, 0, callback);
        }
        if (this->mode == Mode::DEV) {
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
        glfwSwapBuffers(this->gameWindow);
    }

    void GameEngine::shutdown()
    {
        objectLoader->clear();
        info("the Engine was shutdown");
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(this->gameWindow);
        glfwTerminate();
        this->gameRunning = false;

    }

    static void moveInput(GLFWwindow* window, float deltaTime){
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);

    }

    void GameEngine::run() {
        float deltaTime;
        float lastFrame = 0.0f;
        this->gameRunning = true;
        int frame = 0;
        NanoTime frameCounter = 0;
        NanoTime lastTime = utility::getNowNanoTime();
        double unprocessedTime = 0.0;
        while(this->gameRunning){
            boolean render = false;
            NanoTime startTime = utility::getNowNanoTime();
            NanoTime passedTime = startTime - lastTime;
            lastTime = startTime;
            unprocessedTime += (double) passedTime / NANOSECOND;
            auto currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            moveInput(gameWindow, deltaTime);
            frameCounter += passedTime;
            while(unprocessedTime > FRAMERATE){
                render = true;
                unprocessedTime -= FRAMERATE;
                //end engine
                if (glfwWindowShouldClose(gameWindow)) {
                    shutdown();
                    break;
                }
                if(frameCounter >= NANOSECOND){
                    gameFPS = frame;
                    frame = 0;
                    frameCounter = 0;
                }
            }
            if(render){
                this->render();
                frame++;
            }
        }
    }

    void GameEngine::update() {

    }

}
