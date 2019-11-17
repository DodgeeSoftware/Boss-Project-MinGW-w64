#include "Texture.h"

bool Texture::load(const char* filename)
{
    texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y);
    if (texture != 0)
	{
        glBindTexture(GL_TEXTURE_2D, texture);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
        glBindTexture(GL_TEXTURE_2D, 0);
        return true;
	}
	std::cout << "SOIL loading error: " << SOIL_last_result() << std::endl;
	return false;
}

void Texture::free()
{
    glDeleteTextures(1, &texture);
    texture = 0;
    width = 0;
    height = 0;
}

void Texture::draw(float x, float y)
{
    if (texture != 0)
    {
        glPushMatrix();
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(x, y, 0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_QUADS);
                glTexCoord2f(0, 1); glVertex2f(0, 0);
                glTexCoord2f(1, 1); glVertex2f(width, 0);
                glTexCoord2f(1, 0); glVertex2f(width, height);
                glTexCoord2f(0, 0); glVertex2f(0, height);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0);
        glPopMatrix();
    }
}

void Texture::draw(OGLRect source, OGLRect destination)
{
// TODO: This function should simply render a region of a texture no more animation
    if (texture != 0)
    {
        glPushMatrix();
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(destination.x, destination.y, 0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_QUADS);
                glTexCoord2f((source.x / width), (source.y + source.h) / height); glVertex2f(0, 0);
                glTexCoord2f((source.x + source.w) / width, (source.y + source.h) / height); glVertex2f(destination.w, 0);
                glTexCoord2f((source.x + source.w) / width, (source.y) / height); glVertex2f(destination.w, destination.h);
                glTexCoord2f((source.x / width), (source.y) / height); glVertex2f(0, destination.h);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0);
        glPopMatrix();
    }
}




