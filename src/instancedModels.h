#pragma once

#include "model.h"

namespace LJGL{

class instancedModel : protected model{
protected:
    VBO m_instanced_vbo;
    VBO_layout m_instanced_layout;
    unsigned int m_instance_count = 0;

public:
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