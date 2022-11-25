#pragma once

#include "model.h"

namespace LJGL{

class instancedModel : public model{
protected:
    VBO m_instanced_vbo;
    VBO_layout m_instanced_layout;
    unsigned int m_instance_count = 0;
    unsigned int MAX_INSTANCES;
    std::vector<float> m_instance_positions;

public:
    instancedModel(unsigned int maxInstances){
        this->MAX_INSTANCES = maxInstances;
        this->m_instance_positions.resize(this->MAX_INSTANCES * 3);
    }

    // Putting this function here so I can manage the VAO quickly and easily
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
        this->m_instanced_vbo.generate(this->m_instance_positions, this->MAX_INSTANCES * 3 * sizeof(float));
        // Create the VAO:
        this->m_layout; // THIS IS ASSUMED !!!!! HARD CODED !!!!! BAD !!!!!
        this->m_layout.pushFloat(3);
        this->m_layout.pushFloat(3);
        this->m_layout.pushFloat(2);
        this->m_instanced_layout.pushFloat(3);
        this->m_vao.addBuffer(this->m_vbo, this->m_layout);
        this->m_vao.addBuffer(this->m_instanced_vbo, this->m_instanced_layout);
        this->m_vao.enableAttribDivisorOnLastBuffer(1);
    }

    void addInstancePoint(float x, float y, float z){ // An overload in case you dont feel like using glm
        if(this->m_instance_count < this->MAX_INSTANCES){
            this->m_instance_positions[this->m_instance_count * 3] = x;
            this->m_instance_positions[this->m_instance_count * 3 + 1] = y;
            this->m_instance_positions[this->m_instance_count * 3 + 2] = z;
            this->m_instance_count++;
        }else{
            std::cout << "Error: Maximum number of instances reached" << std::endl;
            std::cout << "This error should be handled better later (it should crash your program to punish you for being stupid)" << std::endl;
        }
        this->m_instanced_vbo.subData(this->m_instance_positions, this->m_instance_positions.size() * sizeof(float));
    }

    void setInstanceVBO(std::vector<float> data){
        this->m_instanced_vbo.subData(data, sizeof(data));
    }

    void draw(){
        this->setTransformUniforms();
        if(this->m_texture.textureLoaded){ // This class doesnt support texture units yet
            this->m_texture.bind();
        }
        this->m_shader.use();
        this->m_vao.bind();
        if(this->has_ebo){
            this->m_ebo.bind();
            glDrawElementsInstanced(GL_TRIANGLES, this->m_ebo.getSize(), GL_UNSIGNED_INT, 0, this->m_instance_count);
        }else{
            glDrawArraysInstanced(GL_TRIANGLES, 0, this->m_layout.getStride(), this->m_instance_count);
        }
    }
};

}