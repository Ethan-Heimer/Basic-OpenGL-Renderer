#include "Application.hpp"
#include "Assets/JSONLoading.h"

#include <sstream>
#include <fstream>

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

#include "Objects/object.h"

using json = nlohmann::json;

Application::ErrorCode Assets::JsonLoader::LoadObjects(std::string path){ 
    std::ifstream jsonFile{path};
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

    return Application::Errors::SUCCSESS;
}
