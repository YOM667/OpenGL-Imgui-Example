#include "EngineGL.h"

GLFWwindow* initGLFW(const char* name, int width = 700, int height = 700)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create window
    GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (window == NULL)
    {
        return NULL;
    }
    else
    {
        setCenter(window, width, height);
        glfwMakeContextCurrent(window);
        return window;
    }
}

void setCenter(GLFWwindow* window, int width, int height)
{
    int max_width = GetSystemMetrics(SM_CXSCREEN);
    int max_hieght = GetSystemMetrics(SM_CYSCREEN);
    glfwSetWindowMonitor(window, NULL, (max_width / 2) - (width / 2), (max_hieght / 2) - (height / 2), width, height, GLFW_DONT_CARE);
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