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
        this->cam = &camera(window);
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

    template<typename T> // Allows for any child of model to be added to the world
    void addModel(T m){
        this->models.push_back(m);
    }

    // Full file path for the model to be loaded
    void addLoadModel(std::string path){
        model m(path);
        this->models.push_back(m);
    }

    // File path ommiting the file extensions (.vbo and .ebo will be added automatically)
    void addLoadModel_EBO(std::string path){
        model_EBO m(path);
        this->models.push_back(m);
    }

};

}
