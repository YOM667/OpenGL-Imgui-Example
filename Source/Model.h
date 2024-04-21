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
#include <vector>

#include "EngineGL.h"
#include "Logger.h"
namespace youm::engine
{
    class Model
    {
    public:
        Model(unsigned int id,unsigned int vertexCount);
        unsigned int id;
        unsigned int vertexCount;
    };

    class ObjectLoader
    {
    public:
        ~ObjectLoader();
        Model * loadModel(const float vertices[], int length);
        void clear() const;
        void bind() const;
        void unbind() const;
    private:
        GLuint createVAO() const;
        void createVBO(const float data[],int length) ;
        void setAttributePointer(int attribNum, int vertexCount, int offset);

        std::vector<GLuint>* VAOs;
        std::vector<GLuint>* VBOs;
    };
}


