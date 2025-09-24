#include "Input/Input.h"
#include "Application.hpp"
#include <GLFW/glfw3.h>


bool Input::GetKeyDown(Key key){    
    auto window = Application::Window::GetWindow();
    return glfwGetKey(window, key) == GLFW_PRESS;
}
