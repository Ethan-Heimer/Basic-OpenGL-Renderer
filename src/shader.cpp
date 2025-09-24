#include "Shaders/shaders.h"

#include "glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<Material*> Material::materials{};

void Material::DestroyAll(){
    for(auto o : materials){
        delete o;
    }

    materials.clear();
}

Material::Material(std::string vectorFile, std::string fragmentFile)
{
    std::string vectorCode, fragmentCode;
    bool read = OpenShaderFiles(vectorFile, fragmentFile, 
                                          vectorCode, fragmentCode);
    if(read){
        CompileShaders(vectorCode, fragmentCode, programID);
        materials.push_back(this);
    }
    else
        std::cerr << "Shader Files Could not be opened" << std::endl;
}

Material::~Material(){
    Destroy();
}

void Material::Use(){
    glUseProgram(programID);
}

void Material::Destroy(){
    glDeleteProgram(programID);
}

void Material::SetFloat(std::string name, float value){
    unsigned int uniformLocation = glGetUniformLocation(programID, name.c_str()); 
    glUniform1f(uniformLocation, value);
}

void Material::SetVec3(std::string name, float x, float y, float z){
    unsigned int uniformLocation = glGetUniformLocation(programID, name.c_str()); 
    glUniform3f(uniformLocation, x, y, x);
}

std::vector<Material*> Material::GetMaterials(){
    return materials;
}


bool Material::OpenShaderFiles(const std::string vertexPath, const std::string fragPath,
                             std::string& vertexCode, std::string& fragCode){
    std::ifstream vertexFile, fragFile; 

    try{
        //open files 
        vertexFile.open("../shaders/" + vertexPath);
        fragFile.open("../shaders/" + fragPath);
            
        std::stringstream vertexStream, fragStream;
            
        vertexStream << vertexFile.rdbuf();
        fragStream << fragFile.rdbuf();
            
        vertexCode = vertexStream.str();
        fragCode = fragStream.str();
            
        vertexFile.close();
        fragFile.close();
                
        return true;
    }
    catch(std::ifstream::failure e){
        std::cout << e.what() << std::endl;
        std::cout << e.code() << std::endl;

        return false;
    }
}

bool Material::CompileShaders(const std::string vertexCode, const std::string fragmentCode,
                            unsigned int& programID){
    const int SHADER_SOURCE_COUNT = 1; 
    const int* SHADER_STRING_LENGTH_ARRAY = NULL; 
    const int LOG_BUFFER_SIZE = 512;
            
    const char* vertexSource = vertexCode.c_str();
    const char* fragSource = fragmentCode.c_str();

    int success = 0;
    char infoLog[LOG_BUFFER_SIZE];

    //compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, SHADER_SOURCE_COUNT, &vertexSource, SHADER_STRING_LENGTH_ARRAY);
    glCompileShader(vertexShader);

    //check for errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, LOG_BUFFER_SIZE, NULL, infoLog);
        std::cerr << "SHADER: VERTEX ERROR\n" << infoLog << std::endl;
        return false;
    }
            
    //compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, SHADER_SOURCE_COUNT, &fragSource, SHADER_STRING_LENGTH_ARRAY);
    glCompileShader(fragmentShader);

    //check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, LOG_BUFFER_SIZE, NULL, infoLog);
        std::cerr << "SHADER: FRAGMENT ERROR\n" << infoLog << std::endl;
        return false;
    }

    //link shaders
    unsigned int shader;
    shader = glCreateProgram();

    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shader, LOG_BUFFER_SIZE, NULL, infoLog);
        std::cerr << "SHADER: LINKING ERROR\n" << infoLog << std::endl;
        return false;
    }

    programID = shader;

    //shaders not needed after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}
