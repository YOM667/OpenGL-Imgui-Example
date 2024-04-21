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

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace youm::engine{
    class Shader
    {
    public:
        unsigned int ID;
        Shader(const char* vertexPath, const char* fragmentPath);
        void use() const;

        void setInt(const char *name, int num) const;
        void setFloat(const char *name, float num) const;
        void setDouble(const char *name, double num) const;
        void setBool(const char *name, bool value) const;
        void setUniformF(const char* name, std::vector<float> args) const;
        void setMatrix2F(const char* name, const glm::mat2 &mat2) const;
        void setMatrix3F(const char* name, const glm::mat3 &mat3) const;
        void setMatrix4F(const char* name, glm::mat4 mat4) const;
    private:
        static void checkCompileErrors(unsigned int shader, std::string type);
    };
}
