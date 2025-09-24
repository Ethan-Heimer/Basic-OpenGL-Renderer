#include "Shaders/shaders.h"

#include "glad/glad.h"
#include <vector>

#include "Objects/object.h"

std::vector<Object*> Object::objects{};

void Object::DestroyAll(){
    for(auto o : objects){
        delete o;
    }

    objects.clear();
}

Object::Object(std::vector<float> verticies,
               std::vector<unsigned int> indicies,
               std::vector<float> colors){          

    objects.push_back(this);

    indiciesCount = indicies.size();

    int length = verticies.size();
    std::vector<float> data;

    for(int i = 0; i < length; i++){
        for(int v = 0; v < 3; v++)
            data.push_back(verticies[(i * 3) + v]);

        for(int c = 0; c < 3; c++)
            data.push_back(colors[(i * 3) + c]);
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicies.size(), indicies.data(), GL_STATIC_DRAW);

    //buffer hinting
    //vertex hinting
    //(location, vec*, type, ..., stride, offest)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color hinting
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Object::~Object(){
    Destroy();
}

unsigned int Object::GetVAO() const {
    return VAO;
}

Material* Object::GetMaterial() const {
    return material;
}

void Object::SetMaterial(Material* material){
    this->material = material;
}

int Object::GetIndiciesCount() const {
    return indiciesCount;
}

void Object::Destroy(){ 
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

std::vector<Object*> Object::GetObjectList(){
    return objects;
}



