#ifndef APPLICATION_H
#define APPLICATION_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

//just a temp solition
class Application{
    public:
        int Initialize();
        int Run();
        int Shutdown();

    private:
        GLFWwindow* window;        
};

#endif
