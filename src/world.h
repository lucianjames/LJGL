#include <glad/glad.h>

#include "model.h"
#include "camera.h"

namespace LJGL{

class world{
protected:
    camera* cam;
    GLFWwindow* window;

public:
    std::vector<model> models;
    std::vector<model_EBO> models_EBO; // This is hacky, need to make the model class more flexible.

    world(GLFWwindow* window){
        this->cam = new camera(window);
        this->window = window;
    }
    
    void render(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
        this->cam->processInput();
        for(auto &m : models_EBO){
            m.m_projection = this->cam->getPerspectiveMatrix();
            m.m_view = this->cam->getViewMatrix();
            m.draw();
        }
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }

    unsigned int addLoadModel_EBO(std::string path){
        model_EBO m;
        this->models_EBO.push_back(m);
        this->models_EBO.back().readVBO(path + ".vbo");
        this->models_EBO.back().readEBO(path + ".ebo");
        return this->models_EBO.size() - 1;
    }

};

}
