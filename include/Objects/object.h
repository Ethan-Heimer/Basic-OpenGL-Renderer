#ifndef OBJECT_H
#define OBJECT_H

#include "Shaders/shaders.h"
#include "glad/glad.h"
#include <vector>

class Object{
    public:
        static std::vector<Object*> GetObjectList();
        static void DestroyAll();

        Object(std::vector<float> verticies,
               std::vector<unsigned int> indicies,
               std::vector<float> colors); 

        ~Object();

        unsigned int GetVAO()const; 
        Material* GetMaterial()const; 
        void SetMaterial(Material* material);
        int GetIndiciesCount() const; 
        void Destroy();

    private:
        static std::vector<Object*> objects;

        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

        Material* material;
        unsigned int indiciesCount;
};


#endif
