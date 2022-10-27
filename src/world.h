#include <glad/glad.h>

#include "model.h"
#include "camera.h"

namespace LJGL{

class world{
public:
    camera* cam;
    GLFWwindow* window;
    std::vector<model_EBO*> models;

    world(GLFWwindow* window){
        this->cam = new camera(window);
        this->window = window;
    }
    ~world(){
        delete cam;
        for(auto model : models){
            delete model;
        }
    }
    
    void createAddModel(std::string path){
        model_EBO* model = new model_EBO(path);
        this->models.push_back(model);
    }

    void render(){ // Also handles input
        this->cam->processInput();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for(auto m : models){
            m->m_view = this->cam->getViewMatrix();
            m->m_projection = this->cam->getPerspectiveMatrix();
            m->draw();
        }
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }

};

}
