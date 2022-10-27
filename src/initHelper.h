/*
    This file isnt really that good.....
    I wouldnt rely on it too much.
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace LJGL{

void basic_framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

GLFWwindow* init(int w, int h, const char* title, int glfw_version_major, int glfw_version_minor, bool use_compat=false){
    if(!glfwInit()){ 
        std::cout << "Error: Could not initialize GLFW" << std::endl; 
        return; 
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfw_version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfw_version_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, (use_compat)? GLFW_OPENGL_COMPAT_PROFILE : GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(w, h, title, NULL, NULL);
    if(window == NULL){
        std::cout << "Error: Could not create window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, basic_framebuffer_size_callback);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glEnable(GL_CULL_FACE); // Cull back faces
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set the background color to a dark grey.
}

}