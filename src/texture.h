#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <glad/glad.h>
#include <iostream>

namespace LJGL{

class texture {
private:
    unsigned int textureID;
    int width, height, nrChannels = 0;

public:
    bool textureLoaded = false;

    void createTexture(const char* path){
        glGenTextures(1, &this->textureID);
        glBindTexture(GL_TEXTURE_2D, this->textureID);
        // set the texture wrapping/filtering options (on the currently bound texture object):
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture:
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char* data = stbi_load(path, &this->width, &this->height, &this->nrChannels, 0);
        if (data){
            glTexImage2D(GL_TEXTURE_2D, 0, (this->nrChannels>3)?GL_RGBA:GL_RGB, this->width, this->height, 0, (this->nrChannels>3)?GL_RGBA:GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else{
            std::cout << "ERR: Failed to load texture " << path << std::endl;
        }
        stbi_image_free(data);
        this->textureLoaded = true;
    }

    void createEmptyTexture(unsigned int w, unsigned int h){
        glGenTextures(1, &this->textureID);
        glBindTexture(GL_TEXTURE_2D, this->textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glGenerateMipmap(GL_TEXTURE_2D);
        this->textureLoaded = true;
    }

    void bind() {
        glBindTexture(GL_TEXTURE_2D, this->textureID);
    }

    void bindUnit(unsigned int unit) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, this->textureID);
    }

    // TODO: more texture options
};

}