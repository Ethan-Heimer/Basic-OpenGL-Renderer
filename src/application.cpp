#include "Application.hpp"

#include <iostream>
#include <vector>

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

#include "Shaders/shaders.h"
#include "Objects/object.h"

#define RENDERER_ERROR_GLFW_WINDOW_ERROR -1
#define RENDERER_ERROR_GLAD_INIT_ERROR -2
#define SHADER_COMPILE_ERROR -3

#define GL_MAJOR 3
#define GL_MINOR 3

const int VIEWPORT_X = 0;
const int VIEWPORT_Y = 0;

using json = nlohmann::json;

bool CheckInput(GLFWwindow* window, unsigned int key){
    return glfwGetKey(window, key) == GLFW_PRESS;
}

int Application::Initialize(){ 
    //initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //grab primary monitor data to render in full screen
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);

    //create window
    window = glfwCreateWindow(mode->width, mode->height, "OpenGL Renderer", 
            primary, NULL);

    if(window == NULL){
        std::cerr << "GLFW Could not create window" << std::endl;
        glfwTerminate();
        return RENDERER_ERROR_GLFW_WINDOW_ERROR;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "GLAD Not Initialized. Aborting,,," << std::endl;
        glfwTerminate();
        return RENDERER_ERROR_GLAD_INIT_ERROR;
    }

    glViewport(0, 0, mode->width, mode->height);
 
    std::ifstream jsonFile{"../data.json"};
    json j = json::parse(jsonFile);

    json jsonObjects = j["objects"];
    int size = jsonObjects.size();

    for(int i = 0; i < size; i++){
        json object = jsonObjects[i];

        std::vector<float> verticies = object["verts"];
        std::vector<float> colors = object["colors"];
        std::vector<unsigned int> indicies = object["indicies"];

        Object* obj = new Object(verticies, indicies, colors);

        std::string fragmentShader = object["fragment"];
        std::string vertexShader = object["vertex"];

        Material* material = new Material(vertexShader, fragmentShader);
        obj->SetMaterial(material);
    }

    return 0;
}

int Application::Run(){
    //render loop
    float step = 0;
    auto objects = Object::GetObjectList();

    while(!glfwWindowShouldClose(window)){ 
        glClearColor(.25f, .25f, .25f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        if(CheckInput(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, true); 

        for(auto o : objects){
            int count = o->GetIndiciesCount();

            Material* material = o->GetMaterial();
            material->Use();

            step += 1;
            material->SetFloat("frame", step);

            glBindVertexArray(o->GetVAO());
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

int Application::Shutdown(){
    //destroy

    auto objects = Object::GetObjectList();
    for(auto o : objects){
        delete o;
    }

    auto materials = Material::GetMaterials();
    for(auto o : materials){
        delete o;
    }

    glfwTerminate();
    return 0;
}
