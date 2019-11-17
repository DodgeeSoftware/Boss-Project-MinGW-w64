#ifndef TEXTURE_H
#define TEXTURE_H

#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <SOIL.h>
#include <iostream>
#include "OGLRect.h"

class Texture
{
    public:
        Texture()
        {
            texture = 0;
            width = 0;
            height = 0;
        }
        virtual ~Texture() {}

        bool load(const char* filename);
        void free();
        void draw(float x, float y);
        void draw(OGLRect source, OGLRect destination);

    public:
        unsigned int getTexture();
        int getWidth();
        int getHeight();

    protected:
        unsigned int texture;
        int width;
        int height;

};

inline unsigned int Texture::getTexture()
{
    return texture;
}

inline int Texture::getWidth()
{
    return width;
}

inline int Texture::getHeight()
{
    return height;
}

#endif // TEXTURE_H
