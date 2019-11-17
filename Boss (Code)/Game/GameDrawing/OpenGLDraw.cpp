#include "OpenGLDraw.h"

// Set the OpenGLDraw singletons instance pointer to 0
OpenGLDraw* OpenGLDraw::pInstance = 0;

void OpenGLDraw::pointSize(float size)
{
    glPointSize(size);
}

void OpenGLDraw::pixelRBGA(float x, float y, int red, int green, int blue, int alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4i(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_POINTS);
            glVertex2i(x, y);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::pixelRBGA(float x, float y, float red, float green, float blue, float alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_POINTS);
            glVertex2i(x, y);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::pixelColour(float x, float y, Colour colour)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_POINTS);
            glVertex2i(x, y);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::lineWidth(float size)
{
    glLineWidth(size);
}

void OpenGLDraw::lineRBGA(float x1, float y1, float x2, float y2, int red, int green, int blue, int alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4i(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::lineRBGA(float x1, float y1, float x2, float y2, float red, float green, float blue, float alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::lineColour(float x1, float y1, float x2, float y2, Colour colour)
{
    //glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::rectangleRBGA(float x1, float y1, float x2, float y2, int red, int green, int blue, int alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4i(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y1);
            glVertex2i(x2, y1);
            glVertex2i(x2, y2);
            glVertex2i(x2, y2);
            glVertex2i(x1, y2);
            glVertex2i(x1, y2);
            glVertex2i(x1, y1);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::rectangleRBGA(float x1, float y1, float x2, float y2, float red, float green, float blue, float alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y1);
            glVertex2i(x2, y1);
            glVertex2i(x2, y2);
            glVertex2i(x2, y2);
            glVertex2i(x1, y2);
            glVertex2i(x1, y2);
            glVertex2i(x1, y1);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::rectangleColour(float x1, float y1, float x2, float y2, Colour colour)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
    //glPushMatrix();
        glLoadIdentity();
        glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y1);
            glVertex2i(x2, y1);
            glVertex2i(x2, y2);
            glVertex2i(x2, y2);
            glVertex2i(x1, y2);
            glVertex2i(x1, y2);
            glVertex2i(x1, y1);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::boxRBGA(float x1, float y1, float x2, float y2, int red, int green, int blue, int alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4i(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_QUADS);
            glTexCoord2d(0.0f, 1.0f); glVertex2i(x1, y1);
            glTexCoord2d(1.0f, 1.0f); glVertex2i(x2, y1);
            glTexCoord2d(1.0f, 0.0f); glVertex2i(x2, y2);
            glTexCoord2d(0.0f, 0.0f); glVertex2i(x1, y2);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::boxRBGA(float x1, float y1, float x2, float y2, float red, float green, float blue, float alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_QUADS);
            glTexCoord2d(0.0f, 1.0f); glVertex2i(x1, y1);
            glTexCoord2d(1.0f, 1.0f); glVertex2i(x2, y1);
            glTexCoord2d(1.0f, 0.0f); glVertex2i(x2, y2);
            glTexCoord2d(0.0f, 0.0f); glVertex2i(x1, y2);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::boxColour(float x1, float y1, float x2, float y2, Colour colour)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_QUADS);
            glTexCoord2d(0.0f, 1.0f); glVertex2i(x1, y1);
            glTexCoord2d(1.0f, 1.0f); glVertex2i(x2, y1);
            glTexCoord2d(1.0f, 0.0f); glVertex2i(x2, y2);
            glTexCoord2d(0.0f, 0.0f); glVertex2i(x1, y2);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::circleRBGA(float x, float y, float radius, int red, int green, int blue, int alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4i(red, green, blue, alpha);
    unsigned int vertices = 32;
    float dtheta = (M_PI * 2) / vertices;
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINE_LOOP);
//            for(float theta = 0; theta <= (M_PI * 2) - dtheta; theta += dtheta)
//            {
//                float u = cos(theta) * radius + x;
//                float v = sin(theta) * radius + y;
//                glVertex2i(u, v);
//            }
            for(float t = 0.0f; t <= 1.0f; t += (1.0f / vertices))
            {
                float theta = t * (2.0f * M_PI);
                float u = cos(theta) * radius + x;
                float v = sin(theta) * radius + y;
                glVertex2i(u, v);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::circleRBGA(float x, float y, float radius, float red, float green, float blue, float alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, alpha);
    unsigned int vertices = 32;
    float dtheta = (M_PI * 2) / vertices;
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINE_LOOP);
//            for(float theta = 0; theta <= (M_PI * 2) - dtheta; theta += dtheta)
//            {
//                float u = cos(theta) * radius + x;
//                float v = sin(theta) * radius + y;
//                glVertex2i(u, v);
//            }
            for(float t = 0.0f; t <= 1.0f; t += (1.0f / vertices))
            {
                float theta = t * (2.0f * M_PI);
                float u = cos(theta) * radius + x;
                float v = sin(theta) * radius + y;
                glVertex2i(u, v);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::circleColour(float x, float y, float radius, Colour colour)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
    unsigned int vertices = 32;
    float dtheta = (M_PI * 2) / vertices;
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINE_LOOP);
//            for(float theta = 0; theta <= (M_PI * 2) - dtheta; theta += dtheta)
//            {
//                float u = cos(theta) * radius + x;
//                float v = sin(theta) * radius + y;
//                glVertex2i(u, v);
//            }
            for(float t = 0.0f; t <= 1.0f; t += (1.0f / vertices))
            {
                float theta = t * (2.0f * M_PI);
                float u = cos(theta) * radius + x;
                float v = sin(theta) * radius + y;
                glVertex2i(u, v);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::filledCircleRBGA(float x, float y, float radius, int red, int green, int blue, int alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4i(red, green, blue, alpha);
    unsigned int vertices = 32;
    float dtheta = (M_PI * 2) / vertices;
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_TRIANGLES);
//            for(float theta = 0; theta <= (M_PI * 2); theta += dtheta)
//            {
//                float u1 = cos(theta) * radius + x;
//                float v1 = sin(theta) * radius + y;
//                float u2 = cos(theta + dtheta) * radius + x;
//                float v2 = sin(theta + dtheta) * radius + y;
//                float u3 = x;
//                float v3 = y;
//                glVertex2i(u1, v1);
//                glVertex2i(u2, v2);
//                glVertex2i(u3, v3);
//            }
            for(float t = 0.0f; t <= 1.0f; t += (1.0f / (float)vertices))
            {
                float theta = t * (2.0f * M_PI);
                float u1 = cos(theta) * radius + x;
                float v1 = sin(theta) * radius + y;
                float u2 = cos(theta + dtheta) * radius + x;
                float v2 = sin(theta + dtheta) * radius + y;
                float u3 = x;
                float v3 = y;
                glVertex2i(u1, v1);
                glVertex2i(u2, v2);
                glVertex2i(u3, v3);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::filledCircleRBGA(float x, float y, float radius, float red, float green, float blue, float alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, alpha);
    unsigned int vertices = 32;
    float dtheta = (M_PI * 2) / vertices;
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_TRIANGLES);
//            for(float theta = 0; theta <= (M_PI * 2); theta += dtheta)
//            {
//                float u1 = cos(theta) * radius + x;
//                float v1 = sin(theta) * radius + y;
//                float u2 = cos(theta + dtheta) * radius + x;
//                float v2 = sin(theta + dtheta) * radius + y;
//                float u3 = x;
//                float v3 = y;
//                glVertex2i(u1, v1);
//                glVertex2i(u2, v2);
//                glVertex2i(u3, v3);
//            }
            for(float t = 0.0f; t <= 1.0f; t += (1.0f / (float)vertices))
            {
                float theta = t * (2.0f * M_PI);
                float u1 = cos(theta) * radius + x;
                float v1 = sin(theta) * radius + y;
                float u2 = cos(theta + dtheta) * radius + x;
                float v2 = sin(theta + dtheta) * radius + y;
                float u3 = x;
                float v3 = y;
                glVertex2i(u1, v1);
                glVertex2i(u2, v2);
                glVertex2i(u3, v3);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::filledCircleColour(float x, float y, float radius, Colour colour)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
    unsigned int vertices = 32;
    float dtheta = (M_PI * 2) / vertices;
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_TRIANGLES);
//            for(float theta = 0; theta <= (M_PI * 2); theta += dtheta)
//            {
//                float u1 = cos(theta) * radius + x;
//                float v1 = sin(theta) * radius + y;
//                float u2 = cos(theta + dtheta) * radius + x;
//                float v2 = sin(theta + dtheta) * radius + y;
//                float u3 = x;
//                float v3 = y;
//                glVertex2i(u1, v1);
//                glVertex2i(u2, v2);
//                glVertex2i(u3, v3);
//            }
            for(float t = 0.0f; t <= 1.0f; t += (1.0f / (float)vertices))
            {
                float theta = t * (2.0f * M_PI);
                float u1 = cos(theta) * radius + x;
                float v1 = sin(theta) * radius + y;
                float u2 = cos(theta + dtheta) * radius + x;
                float v2 = sin(theta + dtheta) * radius + y;
                float u3 = x;
                float v3 = y;
                glVertex2i(u1, v1);
                glVertex2i(u2, v2);
                glVertex2i(u3, v3);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::ellipseRBGA(float x, float y, float rx, float ry, int red, int green, int blue, int alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4i(red, green, blue, alpha);
    unsigned int vertices = 32;
    float dtheta = (M_PI * 2) / vertices;
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINE_LOOP);
            for(float theta = 0; theta <= (M_PI * 2) - dtheta; theta += dtheta)
            {
                float u = cos(theta) * rx + x;
                float v = sin(theta) * ry + y;
                glVertex2i(u, v);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::ellipseRBGA(float x, float y, float rx, float ry, float red, float green, float blue, float alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, alpha);
    unsigned int vertices = 32;
    float dtheta = (M_PI * 2) / vertices;
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINE_LOOP);
            for(float theta = 0; theta <= (M_PI * 2) - dtheta; theta += dtheta)
            {
                float u = cos(theta) * rx + x;
                float v = sin(theta) * ry + y;
                glVertex2i(u, v);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::ellipseColour(float x, float y, float rx, float ry, Colour colour)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
    unsigned int vertices = 32;
    float dtheta = (M_PI * 2) / vertices;
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINE_LOOP);
            for(float theta = 0; theta <= (M_PI * 2) - dtheta; theta += dtheta)
            {
                float u = cos(theta) * rx + x;
                float v = sin(theta) * ry + y;
                glVertex2i(u, v);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::filledEllipseRBGA(float x, float y, float rx, float ry, int red, int green, int blue, int alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4i(red, green, blue, alpha);
    unsigned int vertices = 32;
    float dtheta = (M_PI * 2) / vertices;
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_TRIANGLES);
            for(float theta = 0; theta <= (M_PI * 2); theta += dtheta)
            {
                float u1 = cos(theta) * rx + x;
                float v1 = sin(theta) * ry + y;
                float u2 = cos(theta + dtheta) * rx + x;
                float v2 = sin(theta + dtheta) * ry + y;
                float u3 = x;
                float v3 = y;
                glVertex2i(u1, v1);
                glVertex2i(u2, v2);
                glVertex2i(u3, v3);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::filledEllipseRBGA(float x, float y, float rx, float ry, float red, float green, float blue, float alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, alpha);
    unsigned int vertices = 32;
    float dtheta = (M_PI * 2) / vertices;
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_TRIANGLES);
            for(float theta = 0; theta <= (M_PI * 2); theta += dtheta)
            {
                float u1 = cos(theta) * rx + x;
                float v1 = sin(theta) * ry + y;
                float u2 = cos(theta + dtheta) * rx + x;
                float v2 = sin(theta + dtheta) * ry + y;
                float u3 = x;
                float v3 = y;
                glVertex2i(u1, v1);
                glVertex2i(u2, v2);
                glVertex2i(u3, v3);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::filledEllipseColour(float x, float y, float rx, float ry, Colour colour)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
    unsigned int vertices = 32;
    float dtheta = (M_PI * 2) / vertices;
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_TRIANGLES);
            for(float theta = 0; theta <= (M_PI * 2); theta += dtheta)
            {
                float u1 = cos(theta) * rx + x;
                float v1 = sin(theta) * ry + y;
                float u2 = cos(theta + dtheta) * rx + x;
                float v2 = sin(theta + dtheta) * ry + y;
                float u3 = x;
                float v3 = y;
                glVertex2i(u1, v1);
                glVertex2i(u2, v2);
                glVertex2i(u3, v3);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::triangleRBGA(float x1, float y1, float x2, float y2, float x3, float y3, int red, int green, int blue, int alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4i(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
            glVertex2i(x2, y2);
            glVertex2i(x3, y3);
            glVertex2i(x3, y3);
            glVertex2i(x1, y1);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::triangleRBGA(float x1, float y1, float x2, float y2, float x3, float y3, float red, float green, float blue, float alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
            glVertex2i(x2, y2);
            glVertex2i(x3, y3);
            glVertex2i(x3, y3);
            glVertex2i(x1, y1);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::triangleColour(float x1, float y1, float x2, float y2, float x3, float y3, Colour colour)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
            glVertex2i(x2, y2);
            glVertex2i(x3, y3);
            glVertex2i(x3, y3);
            glVertex2i(x1, y1);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::filledTriangleRBGA(float x1, float y1, float x2, float y2, float x3, float y3, int red, int green, int blue, int alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4i(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_TRIANGLES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
            glVertex2i(x3, y3);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::filledTriangleRBGA(float x1, float y1, float x2, float y2, float x3, float y3, float red, float green, float blue, float alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_TRIANGLES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
            glVertex2i(x3, y3);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::filledTriangleColour(float x1, float y1, float x2, float y2, float x3, float y3, Colour colour)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_TRIANGLES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
            glVertex2i(x3, y3);
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::polygonRGBA(float* vx, float* vy, int n, int red, int green, int blue, int alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4i(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINE_LOOP);
            for(int i = 0; i < n; i++)
            {
                glVertex2i(vx[i], vy[i]);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::polygonRGBA(float* vx, float* vy, int n, float red, float green, float blue, float alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINE_LOOP);
            for(int i = 0; i < n; i++)
            {
                glVertex2i(vx[i], vy[i]);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::polygonColour(float* vx, float* vy, int n, Colour colour)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_LINE_LOOP);
            for(int i = 0; i < n; i++)
            {
                glVertex2i(vx[i], vy[i]);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::filledPolygonRGBA(float* vx, float* vy, int n, int red, int green, int blue, int alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4i(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_POLYGON);
            for(int i = 0; i < n; i++)
            {
                glVertex2i(vx[i], vy[i]);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::filledPolygonRGBA(float* vx, float* vy, int n, float red, float green, float blue, float alpha)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_POLYGON);
            for(int i = 0; i < n; i++)
            {
                glVertex2i(vx[i], vy[i]);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::filledPolygonColour(float* vx, float* vy, int n, Colour colour)
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
    //glPushMatrix();
        //glLoadIdentity();
        glBegin(GL_POLYGON);
            for(int i = 0; i < n; i++)
            {
                glVertex2i(vx[i], vy[i]);
            }
        glEnd();
    //glPopMatrix();
}

void OpenGLDraw::enableTexture()
{
    // Enable Texture
    glEnable(GL_TEXTURE_2D);
}

void OpenGLDraw::disableTexture()
{
    // Disable Texture
    glDisable(GL_TEXTURE_2D);
}

void OpenGLDraw::setTexture(unsigned int textureID)
{
    // Bind Texture
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void OpenGLDraw::enableBlending()
{
    // Enable Blending
    glEnable(GL_BLEND);
}

void OpenGLDraw::disableBlending()
{
    // Disable Blending
    glDisable(GL_BLEND);
}

void OpenGLDraw::setBlendMode(int sFactor, int gFactor)
{
    // Set the Blend Mode
    glBlendFunc(sFactor, gFactor);
}

void OpenGLDraw::enableStipple()
{
    // Enable Line Stipple
    glEnable(GL_LINE_STIPPLE);
}

void OpenGLDraw::disableStipple()
{
    // Disable Line Stipple
    glDisable(GL_LINE_STIPPLE);
}

void OpenGLDraw::setLineStipple(int factor, unsigned short pattern)
{
    // Stipple
    glLineStipple(factor, pattern);
}

/*
void OpenGLDraw::bindToLua(lua_State* pLuaState)
{
    // Bind functions to lua state
    luabind::module(pLuaState)
    [
        luabind::class_<OpenGLDraw>("OpenGLDraw")
        //.def(luabind::constructor<>())
        //.def("pointSize", (void (OpenGLDraw::*)(float)) &OpenGLDraw::pointSize)
        .scope
        [
            luabind::def("getInstance", &(OpenGLDraw::getInstance))
        ]

        .def("pointSize", (void (OpenGLDraw::*)(float)) &OpenGLDraw::pointSize)
        .def("pixelRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float)) &OpenGLDraw::pixelRBGA)
        //.def("pixelRBGA", (void (OpenGLDraw::*)(float, float, int, int, int, int)) &OpenGLDraw::pixelRBGA)
        .def("pixelColour", (void (OpenGLDraw::*)(float, float, Colour)) &OpenGLDraw::pixelColour)
        .def("lineWidth", (void (OpenGLDraw::*)(float)) &OpenGLDraw::lineWidth)
        //.def("lineRBGA", (void (OpenGLDraw::*)(float, float, float, float, int, int, int, int)) &OpenGLDraw::lineRBGA)
        .def("lineRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float, float)) &OpenGLDraw::lineRBGA)
        .def("lineColour", (void (OpenGLDraw::*)(float, float, float, float, Colour)) &OpenGLDraw::lineColour)
        //.def("rectangleRBGA", (void (OpenGLDraw::*)(float, float, float, float, int, int, int, int)) &OpenGLDraw::rectangleRBGA)
        .def("rectangleRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float, float)) &OpenGLDraw::rectangleRBGA)
        .def("rectangleColour", (void (OpenGLDraw::*)(float, float, float, float, Colour)) &OpenGLDraw::rectangleColour)
        //.def("boxRBGA", (void (OpenGLDraw::*)(float, float, float, float, int, int, int, int)) &OpenGLDraw::boxRBGA)
        .def("boxRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float, float)) &OpenGLDraw::boxRBGA)
        .def("boxColour", (void (OpenGLDraw::*)(float, float, float, float, Colour)) &OpenGLDraw::boxColour)
        //.def("circleRBGA", (void (OpenGLDraw::*)(float, float, float, int, int, int, int)) &OpenGLDraw::circleRBGA)
        .def("circleRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float)) &OpenGLDraw::circleRBGA)
        .def("circleColour", (void (OpenGLDraw::*)(float, float, float, Colour)) &OpenGLDraw::circleColour)
        //.def("filledCircleRBGA", (void (OpenGLDraw::*)(float, float, float, int, int, int, int)) &OpenGLDraw::filledCircleRBGA)
        .def("filledCircleRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float)) &OpenGLDraw::filledCircleRBGA)
        .def("filledCircleColour", (void (OpenGLDraw::*)(float, float, float, Colour)) &OpenGLDraw::filledCircleColour)
        //.def("ellipseRBGA", (void (OpenGLDraw::*)(float, float, float, float, int, int, int, int)) &OpenGLDraw::ellipseRBGA)
        .def("ellipseRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float, float)) &OpenGLDraw::ellipseRBGA)
        .def("ellipseColour", (void (OpenGLDraw::*)(float, float, float, float, Colour)) &OpenGLDraw::ellipseColour)
        //.def("filledEllipseRBGA", (void (OpenGLDraw::*)(float, float, float, float, int, int, int, int)) &OpenGLDraw::filledEllipseRBGA)
        .def("filledEllipseRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float, float)) &OpenGLDraw::filledEllipseRBGA)
        .def("filledEllipseColour", (void (OpenGLDraw::*)(float, float, float, float, Colour)) &OpenGLDraw::filledEllipseColour)
        //.def("triangleRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, int, int, int, int)) &OpenGLDraw::triangleRBGA)
        .def("triangleRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float, float, float, float)) &OpenGLDraw::triangleRBGA)
        .def("triangleColour", (void (OpenGLDraw::*)(float, float, float, float, float, float, Colour)) &OpenGLDraw::triangleColour)
        //.def("filledTriangleRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, int, int, int, int)) &OpenGLDraw::filledTriangleRBGA)
        .def("filledTriangleRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float, float, float, float)) &OpenGLDraw::filledTriangleRBGA)
        .def("filledTriangleColour", (void (OpenGLDraw::*)(float, float, float, float, float, float, Colour)) &OpenGLDraw::filledTriangleColour)
        //.def("polygonRGBA", (void (OpenGLDraw::*)(float*, float*, int, int, int, int, int)) &OpenGLDraw::polygonRGBA)
        .def("polygonRGBA", (void (OpenGLDraw::*)(float*, float*, int, float, float, float, float)) &OpenGLDraw::polygonRGBA)
        .def("polygonColour", (void (OpenGLDraw::*)(float*, float*, int, float, Colour)) &OpenGLDraw::polygonColour)
        //.def("filledPolygonRGBA", (void (OpenGLDraw::*)(float*, float*, int, int, int, int, int)) &OpenGLDraw::filledPolygonRGBA)
        .def("filledPolygonRGBA", (void (OpenGLDraw::*)(float*, float*, int, float, float, float, float)) &OpenGLDraw::filledPolygonRGBA)
        .def("filledPolygonColour", (void (OpenGLDraw::*)(float*, float*, int, float, Colour)) &OpenGLDraw::filledPolygonColour)
    ];
}
*/
