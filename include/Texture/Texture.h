#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>

class Texture{
    public:
        Texture(std::string imagePath);
        ~Texture();

        void Use();
        void Delete();

        static void DeleteTextures();
    private:

        static std::vector<Texture*> textures;
        unsigned int texture;

};

#endif
