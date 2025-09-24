#include "Application.hpp"

#include "Assets/JSONLoading.h"
#include "Input/Input.h"
#include "Renderer/Renderer.h"
#include "Shaders/shaders.h"
#include "Objects/object.h"

const int VIEWPORT_X = 0;
const int VIEWPORT_Y = 0;

using namespace Application;


ErrorCode App::Initialize(){ 
    ErrorCode error;

    glfwInit(); 

    error = Application::Window::CreateWindow();
    EVALUATE_ERROR(error);

    error = Assets::JsonLoader::LoadObjects("../data.json");
    EVALUATE_ERROR(error); 

    return Errors::SUCCSESS;
}

Application::ErrorCode Application::App::Run(){
    auto objects = Object::GetObjectList();
    auto window = Application::Window::GetWindow();

    while(!Window::ShouldClose()){ 
        if(Input::GetKeyDown(GLFW_KEY_ESCAPE))
            Window::Close();

        Renderer::Clear(.1f, .1f, .2f);
        Renderer::IncrementFrame();

        for(auto o : objects){
            ErrorCode error = Renderer::DisplayObject(o);
            EVALUATE_ERROR(error);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return Errors::SUCCSESS;
}

Application::ErrorCode Application::App::Shutdown(){
    Object::DestroyAll();
    Material::DestroyAll();

    glfwTerminate();

    return Errors::SUCCSESS;
}
