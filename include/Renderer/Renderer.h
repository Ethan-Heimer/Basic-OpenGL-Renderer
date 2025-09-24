#ifndef RENDERER_H
#define RENDERER_H

#include "Application.hpp"
#include "Objects/object.h"
class Renderer{
    public:
        static void Clear(float r, float g, float b);
        static Application::ErrorCode DisplayObject(Object* object);
        static void IncrementFrame();

    private:
        static int frame;
};

#endif
