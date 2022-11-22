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
    
    world(GLFWwindow* window, camera* cam){
        this->window = window;
        this->cam = cam;
    }

    int addModel(model m){
        this->models.push_back(m);
        return this->models.size() - 1;
    }

    int createAddModel(std::string path){
        model m;
        m.readVBO(path);
        this->models.push_back(m);
        return this->models.size() - 1;
    }

    int createAddModel_EBO(std::string path){
        model m;
        m.readVBO(path + ".vbo");
        m.readEBO(path + ".ebo");
        this->models.push_back(m);
        return this->models.size() - 1;
    }

    void processInput(){
        this->cam->processInput();
    }

    void render(bool swapBuffers = true){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for(auto m : models){
            m.m_view = this->cam->getViewMatrix();
            m.m_projection = this->cam->getPerspectiveMatrix();
            m.draw();
        }
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }

};

}
