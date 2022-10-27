#include <glad/glad.h>

#include "model.h"
#include "camera.h"

namespace LJGL{

class world{
public:
    camera* cam;
    GLFWwindow* window;
    model_EBO* model;

    world(GLFWwindow* window){
        this->cam = new camera(window);
        this->window = window;
    }
    ~world(){
        delete cam;
        delete model;
    }

};

}
