#pragma once

#include <glad/glad.h>
#include <vector>
#include <string>

namespace LJGL{

class SSBO{
private:
    unsigned int ID;

public:
    ~SSBO(){
        glDeleteBuffers(1, &ID);
    }

    void generate(const void* data, unsigned int size){
        glGenBuffers(1, &this->ID); // Generate 1 buffer
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->ID); // Bind the buffer to the GL_SHADER_STORAGE_BUFFER target
        glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_COPY); // Send the data to the buffer
    }

    void bind(unsigned int shaderID, std::string name){
        unsigned int block_index;
        block_index = glGetProgramResourceIndex(shaderID, GL_SHADER_STORAGE_BLOCK, name.c_str());
        glShaderStorageBlockBinding(shaderID, block_index, 0);
        unsigned int binding_point_index = 0;
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_point_index, this->ID);
    }

};

}