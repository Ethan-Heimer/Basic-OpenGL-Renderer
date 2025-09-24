#include "Application.hpp"

int main(){
    Application::ErrorCode error;
    Application::App app{}; 

    error = app.Initialize();
    EVALUATE_ERROR(error);

    error = app.Run();
    EVALUATE_ERROR(error);

    error = app.Shutdown();
    EVALUATE_ERROR(error);
}








