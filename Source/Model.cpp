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
//
// Created by YouM on 2024/4/21.
//

#include "Model.h"
namespace youm::engine
{
    Model::Model(unsigned int id,unsigned int vertexCount) : id(id), vertexCount(vertexCount){}


    Model * ObjectLoader::loadModel(const float vertices[], int length) {
        VAOs = new std::vector<GLuint>();
        VBOs = new std::vector<GLuint>();
        unsigned int id = createVAO();
        createVBO(vertices,length);
        return new Model(id,length / 3);
    }
    GLuint ObjectLoader::createVAO() const
    {
        GLuint id;
        glGenVertexArrays(1, &id);
        VAOs->push_back(id);
        glBindVertexArray(id);
        return id;
    }
    void ObjectLoader::createVBO(const float data[],int length)
    {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, length, data, GL_STATIC_DRAW);
        VBOs->push_back(vbo);
        setAttributePointer(0, 3, 0);
        setAttributePointer(1, 2, 3);
    }
    void ObjectLoader::setAttributePointer(int attribNum, int vertexCount, int offset)
    {
        glVertexAttribPointer(attribNum, vertexCount, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(attribNum);
    }

    void ObjectLoader::bind() const
    {
        for(auto vao : *VAOs)
        {
            glBindVertexArray(vao);
        }
    }
    void ObjectLoader::unbind() const
    {
        glBindVertexArray(0);
    }
    void ObjectLoader::clear() const
    {
        for(auto vao : *VAOs)
        {
            glDeleteVertexArrays(1,&vao);
        }
        for(auto vbo : *VBOs)
        {
            glDeleteBuffers(1,&vbo);
        }

    }

    ObjectLoader::~ObjectLoader() {
        delete VAOs;
        info("delete vaos");
        delete VBOs;
        info("delete vbos");
    }

}
