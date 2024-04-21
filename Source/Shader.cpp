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

#include "Shader.h"
namespace youm::engine
{

    Shader::Shader(const char* vertexPath, const char* fragmentPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure stream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        this->ID = glCreateProgram();
        glAttachShader(this->ID, vertex);
        glAttachShader(this->ID, fragment);
        glLinkProgram(this->ID);
        checkCompileErrors(this->ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
// activate the shader
// ------------------------------------------------------------------------
    void Shader::use() const
    {
        glUseProgram(this->ID);
    }
// utility uniform functions
// ------------------------------------------------------------------------
    void Shader::setBool(const char *name, bool value) const
    {
        glUniform1i(glGetUniformLocation(this->ID, name), (int)value);
    }
    void Shader::checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
    void Shader::setUniformF(const char* name, std::vector<float> args) const
    {
        int loc = glGetUniformLocation(this->ID, name);
        switch (args.size()) {
            case 1:
                glUniform1f(loc, args[0]);
                break;
            case 2:
                glUniform2f(loc, args[0], args[1]);
                break;
            case 3:
                glUniform3f(loc, args[0], args[1], args[2]);
                break;
            case 4:
                glUniform4f(loc, args[0], args[1], args[2], args[3]);
                break;
        }
    }
    void Shader::setMatrix2F(const char *name, const glm::mat2 &mat2) const {
        int loc = glGetUniformLocation(this->ID, name);
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat2));
    }
    void Shader::setMatrix3F(const char *name, const glm::mat3 &mat3) const {
        int loc = glGetUniformLocation(this->ID, name);
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat3));
    }
    void Shader::setMatrix4F(const char *name, glm::mat4 mat4) const
    {
        int loc = glGetUniformLocation(this->ID, name);
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat4));
    }
    void Shader::setInt(const char *name, int num) const
    {
        int loc = glGetUniformLocation(this->ID, name);
        glUniform1i(loc,num);
    }
    void Shader::setFloat(const char *name, float num) const
    {
        int loc = glGetUniformLocation(this->ID, name);
        glUniform1f(loc,num);
    }
    void Shader::setDouble(const char *name, double num) const
    {
        int loc = glGetUniformLocation(this->ID, name);
        glUniform1d(loc,num);
    }
}
