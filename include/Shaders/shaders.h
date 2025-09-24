#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include <string>
#include <vector>

class Material{
    public:
        Material(std::string vectorFile, std::string fragmentFile);
        ~Material();

        void Use();
        void Destroy();
        void SetFloat(std::string name, float value);
        void SetVec3(std::string name, float x, float y, float z);

        static std::vector<Material*> GetMaterials();
        static void DestroyAll();

    private:
        static std::vector<Material*> materials;

        unsigned int programID;

        bool OpenShaderFiles(const std::string vertexPath, const std::string fragPath,
                             std::string& vertexCode, std::string& fragCode);

        bool CompileShaders(const std::string vertexCode, const std::string fragmentCode,
                            unsigned int& programID);
};

#endif
