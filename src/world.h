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

};

}
