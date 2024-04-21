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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "EngineGL.h"

namespace youm::engine
{

    GLFWwindow* initGLFW(const char* name, int width = 700, int height = 700)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //create gameWindow
        GLFWwindow* window = glfwCreateWindow(width, height, name, nullptr, nullptr);
        if (window == nullptr)
        {
            return nullptr;
        }
        else
        {
            setWindowCenter(window, width, height);
            glfwMakeContextCurrent(window);
            glEnable(GL_DEPTH_TEST);
            return window;
        }
    }

    void setWindowCenter(GLFWwindow* window, int width, int height)
    {
        int max_width = GetSystemMetrics(SM_CXSCREEN);
        int max_hieght = GetSystemMetrics(SM_CYSCREEN);
        glfwSetWindowMonitor(window, nullptr, (max_width / 2) - (width / 2), (max_hieght / 2) - (height / 2), width, height, GLFW_DONT_CARE);
    }

    void initGLEW()
    {
        //load all OpenGL function pointers
        if (glewInit() != GLEW_OK)
        {
            printf("glew init failed");
            glfwTerminate();
        }
    }
    unsigned int loadImage(const char* file, GLint internal_format, GLenum format, int slot)
    {
        unsigned int texture_buffer;
        glGenTextures(1, &texture_buffer);
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, texture_buffer); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        return texture_buffer;
    }
}

