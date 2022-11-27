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
};  

}