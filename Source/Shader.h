#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
class Shader
{
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setBool(const std::string& name, bool value) const;
    void setFloatVector(const char* name, std::vector<float> args) const;
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};