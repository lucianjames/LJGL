#pragma once

#include "model.h"

namespace LJGL{

class instancedModel : public model{
protected:
    VBO m_instanced_vbo;
    VBO_layout m_instanced_layout;
    unsigned int m_instance_count = 0;

public:
    instancedModel(){
        
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
        this->m_instanced_vbo.generate(std::vector<float>{0.0f, 0.0f, 0.0f}, 3 * sizeof(float));
        // Create the VAO:
        this->m_layout; // THIS IS ASSUMED !!!!! HARD CODED !!!!! BAD !!!!!
        this->m_layout.pushFloat(3);
        this->m_layout.pushFloat(3);
        this->m_layout.pushFloat(2);
        this->m_vao.addBuffer(this->m_vbo, this->m_layout);
        this->m_instanced_layout.pushFloat(3);
        this->m_vao.addBuffer(this->m_instanced_vbo, this->m_instanced_layout);
    }

    void addInstancePoint(glm::vec3 point){
        this->m_instanced_vbo.subData(std::vector<float>{point.x, point.y, point.z}, 3 * sizeof(float));
        this->m_instance_count++;
    }
    
    void addInstacePoint(float x, float y, float z){ // An overload in case you dont feel like using glm
        this->m_instanced_vbo.subData(std::vector<float>{x, y, z}, 3 * sizeof(float));
        this->m_instance_count++;
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