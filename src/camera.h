#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Basic first person camera

namespace LJGL{

// Ugly global variables, the callback functions need them
namespace cameraGlobals{
    float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch = 0.0f;
    float lastX = 800.0f / 2.0;
    float lastY = 600.0 / 2.0;
    float fov = 45.0f;
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    bool firstMouse = true;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (cameraGlobals::firstMouse){
        cameraGlobals::lastX = xpos;
        cameraGlobals::lastY = ypos;
        cameraGlobals::firstMouse = false;
    }
    float xoffset = xpos - cameraGlobals::lastX;
    float yoffset = cameraGlobals::lastY - ypos; 
    cameraGlobals::lastX = xpos;
    cameraGlobals::lastY = ypos;
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    cameraGlobals::yaw   += xoffset;
    cameraGlobals::pitch += yoffset;
    if(cameraGlobals::pitch > 89.0f){ cameraGlobals::pitch = 89.0f; }
    if(cameraGlobals::pitch < -89.0f){ cameraGlobals::pitch = -89.0f; }
    glm::vec3 direction;
    direction.x = cos(glm::radians(cameraGlobals::yaw)) * cos(glm::radians(cameraGlobals::pitch));
    direction.y = sin(glm::radians(cameraGlobals::pitch));
    direction.z = sin(glm::radians(cameraGlobals::yaw)) * cos(glm::radians(cameraGlobals::pitch));
    cameraGlobals::cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    cameraGlobals::fov -= (float)yoffset;
}

class camera{
private:
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    GLFWwindow* window;
public:
    camera(GLFWwindow* window){
        this->window = window;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
    }

    glm::mat4 getViewMatrix(){
        return glm::lookAt(this->cameraPos, this->cameraPos + cameraGlobals::cameraFront, cameraGlobals::cameraUp);
    }

    glm::mat4 getPerspectiveMatrix(){
        int m_viewport[4];
        glGetIntegerv(GL_VIEWPORT, m_viewport);
        return glm::perspective(glm::radians(cameraGlobals::fov), (float)m_viewport[2] / (float)m_viewport[3], 0.1f, 100.0f);
    }

    void processMovement(){
        if(glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS){ this->cameraPos += 0.05f * cameraGlobals::cameraFront; }
        if(glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS){ this->cameraPos -= 0.05f * cameraGlobals::cameraFront; }
        if(glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS){ this->cameraPos -= glm::normalize(glm::cross(cameraGlobals::cameraFront, cameraGlobals::cameraUp)) * 0.05f; }
        if(glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS){ this->cameraPos += glm::normalize(glm::cross(cameraGlobals::cameraFront, cameraGlobals::cameraUp)) * 0.05f; }
    }

    void processEscape(){
        // If escape is pressed, free the cursor up
        if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        // If the window is clicked, capture the cursor
        if(glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
            glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    void processInput(){
        this->processMovement();
        this->processEscape();
    }

};

}