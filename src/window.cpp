#include "Application.hpp"
#include <GLFW/glfw3.h>

#define GL_MAJOR 3
#define GL_MINOR 3

using namespace Application;

int Window::width{};
int Window::height{};
GLFWwindow* Window::window;

ErrorCode Window::CreateWindow(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //grab primary monitor data to render in full screen
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);

    //create window
    width = mode->width;
    height = mode->height;

    window = glfwCreateWindow(width, height, "OpenGL Renderer", 
            primary, NULL);

    if(window == NULL){
        glfwTerminate();
        return Errors::ThrowInitError("GLFW Could not create window");
    }

    glfwMakeContextCurrent(window);

    //this is a strange place to put this? but it'll live here for now
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        glfwTerminate();
        return Application::Errors::ThrowInitError("GLAD Was Not be initialized");
    }

    SetViewportSize();

    return Errors::SUCCSESS;    
}

void Window::Close(){
    glfwSetWindowShouldClose(window, true); 
}

bool Window::ShouldClose(){
    return glfwWindowShouldClose(window);
}

GLFWwindow* Window::GetWindow(){
   return window; 
}

void Window::SetViewportSize(){
    SetViewportSize(width, height);
}

void Window::SetViewportSize(int x, int y){ 
    glViewport(0, 0, x, y);
}
