#ifndef __OPENGLDRAW_H
#define __OPENGLDRAW_H

// C/C++ Includes
#include <string>

// Lua
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

// LuaBridge
#include <LuaBridge/LuaBridge.h>

#include "OpenGLDraw.h"

namespace LuaBinding
{
    static void OpenGLDrawBind(lua_State* pLuaState)
    {
        luabridge::getGlobalNamespace(pLuaState)
            .beginClass<OpenGLDraw>("OpenGLDraw")
                .addStaticFunction("getInstance", &(OpenGLDraw::getInstance))
                // Point Size
                .addFunction("pointSize", (void (OpenGLDraw::*)(float)) &OpenGLDraw::pointSize)
                // Line Width
                .addFunction("lineWidth", (void (OpenGLDraw::*)(float)) &OpenGLDraw::lineWidth)
                // Pixel
                .addFunction("pixelRBGA", (void (OpenGLDraw::*)(float, float, int, int, int, int)) &OpenGLDraw::pixelRBGA)
                .addFunction("pixelRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float)) &OpenGLDraw::pixelRBGA)
                .addFunction("pixelColour", (void (OpenGLDraw::*)(float, float, Colour)) &OpenGLDraw::pixelColour)
                // Line
                .addFunction("lineRBGA", (void (OpenGLDraw::*)(float, float, float, float, int, int, int, int)) &OpenGLDraw::lineRBGA)
                .addFunction("lineRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float, float)) &OpenGLDraw::lineRBGA)
                .addFunction("lineColour", (void (OpenGLDraw::*)(float, float, float, float, Colour)) &OpenGLDraw::lineColour)
                // Rectangle
                .addFunction("rectangleRBGA", (void (OpenGLDraw::*)(float, float, float, float, int, int, int, int)) &OpenGLDraw::rectangleRBGA)
                .addFunction("rectangleRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float, float)) &OpenGLDraw::rectangleRBGA)
                .addFunction("rectangleColour", (void (OpenGLDraw::*)(float, float, float, float, Colour)) &OpenGLDraw::rectangleColour)
                // Box
                .addFunction("boxRBGA", (void (OpenGLDraw::*)(float, float, float, float, int, int, int, int)) &OpenGLDraw::boxRBGA)
                .addFunction("boxRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float, float)) &OpenGLDraw::boxRBGA)
                .addFunction("rectangleColour", (void (OpenGLDraw::*)(float, float, float, float, Colour)) &OpenGLDraw::rectangleColour)
                // Circle
                .addFunction("circleRBGA", (void (OpenGLDraw::*)(float, float, float, int, int, int, int)) &OpenGLDraw::circleRBGA)
                .addFunction("circleRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float)) &OpenGLDraw::circleRBGA)
                .addFunction("circleColour", (void (OpenGLDraw::*)(float, float, float, Colour)) &OpenGLDraw::circleColour)
                // Filled Circle
                .addFunction("filledCircleRBGA", (void (OpenGLDraw::*)(float, float, float, int, int, int, int)) &OpenGLDraw::filledCircleRBGA)
                .addFunction("filledCircleRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float)) &OpenGLDraw::filledCircleRBGA)
                .addFunction("filledCircleColour", (void (OpenGLDraw::*)(float, float, float, Colour)) &OpenGLDraw::filledCircleColour)
                // Elipse
                .addFunction("ellipseRBGA", (void (OpenGLDraw::*)(float, float, float, float, int, int, int, int)) &OpenGLDraw::ellipseRBGA)
                .addFunction("ellipseRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float, float)) &OpenGLDraw::ellipseRBGA)
                .addFunction("ellipseColour", (void (OpenGLDraw::*)(float, float, float, float, Colour)) &OpenGLDraw::ellipseColour)
                // Filled Elipse
                .addFunction("filledEllipseRBGA", (void (OpenGLDraw::*)(float, float, float, float, int, int, int, int)) &OpenGLDraw::filledEllipseRBGA)
                .addFunction("filledEllipseRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float, float)) &OpenGLDraw::filledEllipseRBGA)
                .addFunction("filledEllipseColour", (void (OpenGLDraw::*)(float, float, float, float, Colour)) &OpenGLDraw::filledEllipseColour)
                // TODO: Not sure why but these don't work
                /*
                    virtual void triangleRBGA(float x1, float y1, float x2, float y2, float x3, float y3, int red, int green, int blue, int alpha);
                    virtual void triangleRBGA(float x1, float y1, float x2, float y2, float x3, float y3, float red, float green, float blue, float alpha);
                    virtual void triangleColour(float x1, float y1, float x2, float y2, float x3, float y3, Colour colour);
                    virtual void filledTriangleRBGA(float x1, float y1, float x2, float y2, float x3, float y3, int red, int green, int blue, int alpha);
                    virtual void filledTriangleRBGA(float x1, float y1, float x2, float y2, float x3, float y3, float red, float green, float blue, float alpha);
                    virtual void filledTriangleColour(float x1, float y1, float x2, float y2, float x3, float y3, Colour colour);

                    // Triangle
                    //.addFunction("triangleRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, int, int, int, int)) &OpenGLDraw::triangleRBGA)
                    //.addFunction("triangleRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float, float, float, float)) &OpenGLDraw::triangleRBGA)
                    //.addFunction("triangleColour", (void (OpenGLDraw::*)(float, float, float, float, float, float, Colour)) &OpenGLDraw::triangleColour)
                    //// Filled Triangle
                    //.addFunction("filledTriangleRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, int, int, int, int)) &OpenGLDraw::filledTriangleRBGA)
                    //.addFunction("filledTriangleRBGA", (void (OpenGLDraw::*)(float, float, float, float, float, float, float, float, float, float)) &OpenGLDraw::filledTriangleRBGA)
                    //.addFunction("filledTriangleColour", (void (OpenGLDraw::*)(float, float, float, float, float, float, Colour)) &OpenGLDraw::filledTriangleColour)
                */
                // TODO Implement these
                /*
                    virtual void polygonRGBA(float* vx, float* vy, int n, int red, int green, int blue, int alpha);
                    virtual void polygonRGBA(float* vx, float* vy, int n, float red, float green, float blue, float alpha);
                    virtual void polygonColour(float* vx, float* vy, int n, Colour colour);
                    virtual void filledPolygonRGBA(float* vx, float* vy, int n, int red, int green, int blue, int alpha);
                    virtual void filledPolygonRGBA(float* vx, float* vy, int n, float red, float green, float blue, float alpha);
                    virtual void filledPolygonColour(float* vx, float* vy, int n, Colour colour);
                */
                .addFunction("enableTexture", (void (OpenGLDraw::*)()) &OpenGLDraw::enableTexture)
                .addFunction("disableTexture", (void (OpenGLDraw::*)()) &OpenGLDraw::disableTexture)
                .addFunction("setTexture", (void (OpenGLDraw::*)(unsigned int)) &OpenGLDraw::setTexture)
                .addFunction("enableBlending", (void (OpenGLDraw::*)()) &OpenGLDraw::enableBlending)
                .addFunction("disableBlending", (void (OpenGLDraw::*)()) &OpenGLDraw::disableBlending)
                .addFunction("setBlendMode", (void (OpenGLDraw::*)(int, int)) &OpenGLDraw::setBlendMode)
                .addFunction("enableStipple", (void (OpenGLDraw::*)()) &OpenGLDraw::enableStipple)
                .addFunction("disableStipple", (void (OpenGLDraw::*)()) &OpenGLDraw::disableStipple)
                .addFunction("setLineStipple", (void (OpenGLDraw::*)(int, unsigned short)) &OpenGLDraw::setLineStipple)
            .endClass();
    }
}

#endif // __OPENGLDRAW_H

/*


        virtual void polygonRGBA(float* vx, float* vy, int n, int red, int green, int blue, int alpha);
        virtual void polygonRGBA(float* vx, float* vy, int n, float red, float green, float blue, float alpha);
        virtual void polygonColour(float* vx, float* vy, int n, Colour colour);
        virtual void filledPolygonRGBA(float* vx, float* vy, int n, int red, int green, int blue, int alpha);
        virtual void filledPolygonRGBA(float* vx, float* vy, int n, float red, float green, float blue, float alpha);
        virtual void filledPolygonColour(float* vx, float* vy, int n, Colour colour);

        virtual void enableTexture();
        virtual void disableTexture();
        virtual void setTexture(unsigned int textureID);
        virtual void enableBlending();
        virtual void disableBlending();
        virtual void setBlendMode(int sFactor, int gFactor);
        virtual void enableStipple();
        virtual void disableStipple();
        virtual void setLineStipple(int factor, unsigned short pattern);
*/
