#define STB_IMAGE_IMPLEMENTATION
#include "Texture/Texture.h"

#include "glad/glad.h"
#include <iostream>
#include <vector>

#include "Image/stb_image.h"

std::vector<Texture*> Texture::textures;

Texture::Texture(std::string imagePath){
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(imagePath.c_str(), &width, &height,
        &nrChannels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Image Error: " << imagePath << std::endl;
    } 

    glBindTexture(GL_TEXTURE_2D, 0);
    textures.push_back(this); 
}

Texture::~Texture(){
    Delete();
}

void Texture::Use(){
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::Delete(){
    glDeleteTextures(1, &texture);
}

void Texture::DeleteTextures(){
    for(auto o : textures){
        delete o;
    }
}
