#include "Application.hpp"
#include <iostream>

using namespace Application;

int Errors::error{};

void Display(std::string header, std::string message){
    std::cout << header << std::endl;
    std::cout << message << std::endl;
}

ErrorCode Errors::GetError(){
    return error;
}

ErrorCode Errors::ThrowInitError(std::string message){
    Display("Init Error:", message);
    return Errors::INITERROR;
}

ErrorCode Errors::ThrowShaderError(std::string message){
    Display("Shader Error:", message);
    return Errors::SHADERERROR;
}

ErrorCode Errors::ThrowRendererError(std::string message){
    Display("Renderer Error:", message);
    return Errors::RENDERERERROR;
}


