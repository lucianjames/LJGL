#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "shader.h"

namespace LJGL{

class model{
protected:
    VBO m_vbo;
    VAO m_vao;
    EBO m_ebo;
    VBO_layout m_layout;
    bool has_ebo = false;

public:
    shader m_shader;
    glm::mat4 m_model = glm::mat4(1.0f);
    glm::mat4 m_view = glm::mat4(1.0f);
    glm::mat4 m_projection = glm::mat4(1.0f);
    
    void readVBO(std::string path){
        // Create a vector to store the data from the file:
        std::vector<float> VBO_data;
        // Open the file:
        std::ifstream file(path);
        if(!file.is_open()){
            std::cout << "Error: Could not open file " << path << std::endl;
            return;
        }
        // Read the file:
        std::string line;
        while(std::getline(file, line)){
            std::stringstream ss(line);
            std::string token;
            while(std::getline(ss, token, ' ')){
                VBO_data.push_back(std::stof(token));
            }
        }
        // Close the file:
        file.close();
        // Generate the VBO:
        this->m_vbo.generate(VBO_data, VBO_data.size() * sizeof(float));
        // Create the VAO:
        this->m_layout; // THIS IS ASSUMED !!!!! HARD CODED !!!!! BAD !!!!!
        this->m_layout.pushFloat(3);
        this->m_layout.pushFloat(3);
        this->m_layout.pushFloat(2);
        this->m_vao.addBuffer(this->m_vbo, this->m_layout);
    }

    void readEBO(std::string path){
        // Create a vector to store the data from the file:
        std::vector<unsigned int> EBO_data;
        // Open the file:
        std::ifstream file(path);
        if(!file.is_open()){
            std::cout << "Error: Could not open file " << path << std::endl;
            return;
        }
        // Read the file:
        std::string line;
        while(std::getline(file, line)){
            std::stringstream ss(line);
            std::string token;
            while(std::getline(ss, token, ' ')){
                EBO_data.push_back(std::stof(token));
            }
        }
        // Close the file:
        file.close();
        // Generate the EBO:
        this->m_ebo.generate(EBO_data, EBO_data.size() * sizeof(unsigned int));
        this->has_ebo = true;
    }

    void setTransformUniforms(){
        this->m_shader.use();
        this->m_shader.setUniformMat4fv("model", glm::value_ptr(this->m_model));
        this->m_shader.setUniformMat4fv("view", glm::value_ptr(this->m_view));
        this->m_shader.setUniformMat4fv("projection", glm::value_ptr(this->m_projection));
    }

    void draw(){
        this->setTransformUniforms();
        this->m_shader.use();
        this->m_vao.bind();
        if(this->has_ebo){
            this->m_ebo.bind();
            glDrawElements(GL_TRIANGLES, this->m_ebo.getSize(), GL_UNSIGNED_INT, 0);
        }else{
            glDrawArrays(GL_TRIANGLES, 0, this->m_layout.getStride());
        }
    }
};

}