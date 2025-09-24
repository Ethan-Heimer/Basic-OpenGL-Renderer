#ifndef APPLICATION_H
#define APPLICATION_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <string>

#define EVALUATE_ERROR(X)              \
if(X != Application::Errors::SUCCSESS){ \
    return X;                          \
}                                      \

//just a temp solition
namespace Application{ 
    using ErrorCode = int;

    class App{
        public:
            ErrorCode Initialize();
            ErrorCode Run();
            ErrorCode Shutdown();
    };

    class Window{
        public:
            static ErrorCode CreateWindow();
            static GLFWwindow* GetWindow();

            static void SetViewportSize();
            static void SetViewportSize(int x, int y);

            static bool ShouldClose();
            static void Close();
            
        private:
            static int width;
            static int height;
            static GLFWwindow* window;
    };

    class Errors{
        public:
            static const ErrorCode SUCCSESS = 0;

            static const ErrorCode RENDERERERROR = 1;
            static const ErrorCode SHADERERROR = 2;
            static const ErrorCode INITERROR = 3;

            static ErrorCode GetError();

            static ErrorCode ThrowInitError(std::string message);
            static ErrorCode ThrowRendererError(std::string message);
            static ErrorCode ThrowShaderError(std::string message);

        private:
            static ErrorCode error;
    };
};

#endif
