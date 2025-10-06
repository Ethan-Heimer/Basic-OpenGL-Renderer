#include "Renderer/Renderer.h"
#include "Application.hpp"
#include "Texture/Texture.h"

int Renderer::frame{};

void Renderer::IncrementFrame(){
    frame ++;
}

void Renderer::Clear(float r, float g, float b){
    glClearColor(r, g, b, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

Application::ErrorCode Renderer::DisplayObject(Object *object){
    try{
        int count = object->GetIndiciesCount();

        Material* material = object->GetMaterial();
        material->Use();

        Texture* texture = object->GetTexture();
        texture->Use();

        material->SetFloat("frame", frame);

        glBindVertexArray(object->GetVAO());
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        return Application::Errors::SUCCSESS;
    }
    catch(...){
        return Application::Errors::ThrowRendererError("Invalid Data, Cannot Render");
    }
}
