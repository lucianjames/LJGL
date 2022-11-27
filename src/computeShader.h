#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

namespace LJGL{

class computeShader{
public:
    unsigned int ID; // Shader ID, Ideally this wouldnt need to be public

    void createShader(const char* path){
        // Load the shader file
        std::string computeCode;
        std::ifstream cShaderFile;
        cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try{
            cShaderFile.open(path); // Open the file
            std::stringstream cShaderStream; 
            cShaderStream << cShaderFile.rdbuf(); // Read the file into the stringstream
            cShaderFile.close(); // Close the file
            computeCode = cShaderStream.str(); // Convert the stream into a string
        } catch (std::ifstream::failure e){
            std::cout << "ERROR::COMPUTE_SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        }
        const char* cShaderCode = computeCode.c_str(); // Convert the string into a c string
        // Create the compute shader program
        unsigned int compute_shader = glCreateShader(GL_COMPUTE_SHADER);
        glShaderSource(compute_shader, 1, &cShaderCode, NULL);
        glCompileShader(compute_shader);
        this->ID = glCreateProgram();
        glAttachShader(this->ID, compute_shader);
        glLinkProgram(this->ID);
        glDeleteShader(compute_shader);
        // !!!! there is no debug info right now !!!!
    }    

    void use(){
        glUseProgram(this->ID);
    }

    void setUniform4f(const std::string& name, float x, float y, float z, float w){
        this->use();
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    void setUniform3f(const std::string& name, float x, float y, float z){
        this->use();
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    void setUniform2f(const std::string& name, float x, float y){
        this->use();
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    void setUniform1f(const std::string& name, float x){
        this->use();
        glUniform1f(glGetUniformLocation(ID, name.c_str()), x);
    }

    void setUniform4i(const std::string& name, int x, int y, int z, int w){
        this->use();
        glUniform4i(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    void setUniform3i(const std::string& name, int x, int y, int z){
        this->use();
        glUniform3i(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    void setUniform2i(const std::string& name, int x, int y){
        this->use();
        glUniform2i(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    void setUniform1i(const std::string& name, int x){
        this->use();
        glUniform1i(glGetUniformLocation(ID, name.c_str()), x);
    }
    
    void setUniformMat4fv(const std::string& name, const float* matrix){
        this->use();
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, matrix);
    }
    void setUniformMat3fv(const std::string& name, const float* matrix){
        this->use();
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, matrix);
    }
    void setUniformMat2fv(const std::string& name, const float* matrix){
        this->use();
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, matrix);
    }
};  

}