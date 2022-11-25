#pragma once
#include <glad/glad.h>
#include "VBO.h"

namespace LJGL{

class VAO{
private:
    unsigned int ID;
    unsigned int attribOffset = 0;
public:
    VAO(){
        glGenVertexArrays(1, &this->ID);
    }

    ~VAO(){
        glDeleteVertexArrays(1, &this->ID);
    }

    void bind(){
        glBindVertexArray(this->ID);
    }
    
    void addBuffer(VBO& vbo, const VBO_layout& layout){
        this->bind(); // Bind the VAO
        vbo.bind(); // Bind the VBO
        const auto& elements = layout.getElements(); // Get the elements from the layout
        unsigned long long int offset = 0; // long long int is used to avoid overflow under basically any circumstance
        for (int i = 0; i < elements.size(); i++) {
            const auto& element = elements[i]; // Get the element
            glEnableVertexAttribArray(i + attribOffset); // Enable the attribute
            glVertexAttribPointer(i + attribOffset, element.count, element.type, element.normalised, layout.getStride(), (const void*)offset); // Set the attribute
            offset += element.count * VBO_element::getSizeOfType(element.type); // Increase the offset
        }
        this->attribOffset += elements.size(); // Increase the attribOffset for the next VBO to be added
    }

    void enableAttribDivisorOnLastBuffer(unsigned int divisor){
    glVertexAttribDivisor(attribOffset-1, divisor);
}
};

}