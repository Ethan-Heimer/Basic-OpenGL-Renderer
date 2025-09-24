#ifndef JSONLOADER_H
#define JSONLOADER_H

#include "Application.hpp"

namespace Assets{
    class JsonLoader{
        public:   
            static Application::ErrorCode LoadObjects(std::string path);
    };
}

#endif
