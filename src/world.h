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

    world(GLFWwindow* window){
        this->cam = *camera(window);
        this->window = window;
    }
    
    void render(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
        this->cam->processInput();
        for(auto &m : models){
            m.m_projection = this->cam->getPerspectiveMatrix();
            m.m_view = this->cam->getViewMatrix();
            m.draw();
        }
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }

    template<typename T>
    unsigned int addModel(T m){
        this->models.push_back(m);
        return this->models.size() - 1;
    }

    unsigned int addLoadModel(std::string path){
        model m(path);
        this->models.push_back(m);
        return this->models.size() - 1;
    }

    unsigned int addLoadModel_EBO(std::string path){
        model_EBO m(path);
        this->models.push_back(m);
        return this->models.size() - 1;
    }

};

}
