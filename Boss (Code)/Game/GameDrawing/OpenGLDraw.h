#ifndef OPENGLDRAW_H
#define OPENGLDRAW_H

// C/C++ Includes
#include <cmath>

/*
// LUA / LUA BIND Includes
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
*/

//// OpenGL Extension Wrangler Includes
//#include <gl/glew.h>
// OpenGL Includes
#include <gl/gl.h>
//#include <gl/glu.h>

// Drawing Includes
#include "Colour.h"

/** The OpenGLDraw Class is a collection of drawing functions, designed to mirror SDL_GFX.
    It follows a singleton design pattern. So simply include the header as as needed,
    call the GetInstance method and then the function you need **/
class OpenGLDraw
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    /* NOTE: The Contructors/Destructors section is reponsible for creating and
       destroying OpenGLDraw along with setting default parameters */
    public:
        //! Destructor
        virtual ~OpenGLDraw()
        {
            // if there is an instance of the OpenGLDraw class then destroy it.
            if (OpenGLDraw::pInstance != 0)
            {
                // destroy the instance of the OpenGLDraw class
                delete OpenGLDraw::pInstance;
                // ensure that the instance pointer is set to point to nothing
                OpenGLDraw::pInstance = 0;
            }
        }

    protected:
        //! Default Constructor
        OpenGLDraw() {}
        ////! Copy constructor
        //OpenGLDraw(const OpenGLDraw& other) {}

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    /* NOTE: The Overloaded Operators section provides support for overloaded operators.
       In our case we make the assignment operator protected to follow a singleton pattern */
    public:
        // No methods or members

    protected:
        ////! OpenGLDraw Assignment operator
        //OpenGLDraw& operator=(const OpenGLDraw& other) { return *this; }

    // ***********************
    // * SINGLETON FUNCTIONS *
    // ***********************
    /* NOTE: This section is for our singleton functions */
    public:
        //! Create or return a handle to the Game Instance
        static OpenGLDraw* getInstance()
        {
            /* if there is no instance of the game class
               then create one. */
            if (OpenGLDraw::pInstance == 0)
            {
                // create an instance of the OpenGLDraw class
                OpenGLDraw::pInstance = new OpenGLDraw();
            }
            // return the instance of the game engine class
            return OpenGLDraw::pInstance;
        }

    protected:
        // The single instance of the OpenGLDraw class
        static OpenGLDraw* pInstance;

    // *********************
    // * DRAWING FUNCTIONS *
    // *********************

    // DRAWING PROPERTIES
    public:
        //! Set the Point Size
        virtual void pointSize(float size);
        //! Set the Line Width
        virtual void lineWidth(float size);
        // TODO: need to implement stipple functions

    // PIXEL FUNCTIONS
    public:
        //! Draw a Pixel with int RBGA colour values (0-255)
        virtual void pixelRBGA(float x, float y, int red, int green, int blue, int alpha);
        //! Draw a Pixel with float RBGA colour values (0.0f-1.0f)
        virtual void pixelRBGA(float x, float y, float red, float green, float blue, float alpha);
        //! Draw a Pixel with Colour (where colours components are floats)
        virtual void pixelColour(float x, float y, Colour colour);

    // LINE DRAWING FUNCTIONS
    public:
        //! Draw a Line with int RBGA colour values (0-255)
        virtual void lineRBGA(float x1, float y1, float x2, float y2, int red, int green, int blue, int alpha);
        //! Draw a Line with float RBGA colour values (0.0f-1.0f)
        virtual void lineRBGA(float x1, float y1, float x2, float y2, float red, float green, float blue, float alpha);
        //! Draw a Line with Colour (where colours components are floats)
        virtual void lineColour(float x1, float y1, float x2, float y2, Colour colour);

    // RECTANGLES
    public:
        //! Draw a Rectangle with int RBGA colour values (0-255)
        virtual void rectangleRBGA(float x1, float y1, float x2, float y2, int red, int green, int blue, int alpha);
        //! Draw a Rectangle with float RBGA colour values (0.0f-1.0f)
        virtual void rectangleRBGA(float x1, float y1, float x2, float y2, float red, float green, float blue, float alpha);
        //! Draw a Rectangle with Colour (where colours components are floats)
        virtual void rectangleColour(float x1, float y1, float x2, float y2, Colour colour);

    // BOXES
    public:
        //! Draw a Box with int RBGA colour values (0-255)
        virtual void boxRBGA(float x1, float y1, float x2, float y2, int red, int green, int blue, int alpha);
        //! Draw a Box with float RBGA colour values (0.0f-1.0f)
        virtual void boxRBGA(float x1, float y1, float x2, float y2, float red, float green, float blue, float alpha);
        //! Draw a Box with Colour (where colours components are floats)
        virtual void boxColour(float x1, float y1, float x2, float y2, Colour colour);

    // CIRCLES
    public:
        //! Draw a Circle with int RBGA colour values (0-255)
        virtual void circleRBGA(float x, float y, float radius, int red, int green, int blue, int alpha);
        //! Draw a Circle with float RBGA colour values (0.0f-1.0f)
        virtual void circleRBGA(float x, float y, float radius, float red, float green, float blue, float alpha);
        //! Draw a Circle with Colour (where colours components are floats)
        virtual void circleColour(float x, float y, float radius, Colour colour);
        //! Draw a Filled Circle with int RBGA colour values (0-255)
        virtual void filledCircleRBGA(float x, float y, float radius, int red, int green, int blue, int alpha);
        //! Draw a Filled Circle with float RBGA colour values (0.0f-1.0f)
        virtual void filledCircleRBGA(float x, float y, float radius, float red, float green, float blue, float alpha);
        //! Draw a Filled Circle with Colour (where colours components are floats)
        virtual void filledCircleColour(float x, float y, float radius, Colour colour);

    // ELLIPSES
    public:
        //! Draw a Ellipse with int RBGA colour values (0-255)
        virtual void ellipseRBGA(float x, float y, float rx, float ry, int red, int green, int blue, int alpha);
        //! Draw a Ellipse with float RBGA colour values (0.0f-1.0f)
        virtual void ellipseRBGA(float x, float y, float rx, float ry, float red, float green, float blue, float alpha);
        //! Draw a Ellipse with Colour (where colours components are floats)
        virtual void ellipseColour(float x, float y, float radius1, float radius2, Colour colour);
        //! Draw a Filled Ellipse with int RBGA colour values (0-255)
        virtual void filledEllipseRBGA(float x, float y, float rx, float ry, int red, int green, int blue, int alpha);
        //! Draw a Filled Ellipse with float RBGA colour values (0.0f-1.0f)
        virtual void filledEllipseRBGA(float x, float y, float rx, float ry, float red, float green, float blue, float alpha);
        //! Draw a Filled Ellipse with Colour (where colours components are floats)
        virtual void filledEllipseColour(float x, float y, float rx, float ry, Colour colour);

    // Skipped Pie functions (probably utterly useless)
    public:
        // TODO: Very low priority pie drawing functions

    // TRIANGLES
    public:
        //! Draw a Triangle with int RBGA colour values (0-255)
        virtual void triangleRBGA(float x1, float y1, float x2, float y2, float x3, float y3, int red, int green, int blue, int alpha);
        //! Draw a Triangle with float RBGA colour values (0.0f-1.0f)
        virtual void triangleRBGA(float x1, float y1, float x2, float y2, float x3, float y3, float red, float green, float blue, float alpha);
        //! Draw a Triangle with Colour (where colours components are floats)
        virtual void triangleColour(float x1, float y1, float x2, float y2, float x3, float y3, Colour colour);
        //! Draw a Filled Triangle with int RBGA colour values (0-255)
        virtual void filledTriangleRBGA(float x1, float y1, float x2, float y2, float x3, float y3, int red, int green, int blue, int alpha);
        //! Draw a Filled Triangle with float RBGA colour values (0.0f-1.0f)
        virtual void filledTriangleRBGA(float x1, float y1, float x2, float y2, float x3, float y3, float red, float green, float blue, float alpha);
        //! Draw a Filled Triangle with Colour (where colours components are floats)
        virtual void filledTriangleColour(float x1, float y1, float x2, float y2, float x3, float y3, Colour colour);

    // POLYGONS
    public:
        //! Draw a Polygon with int RBGA colour values (0-255)
        virtual void polygonRGBA(float* vx, float* vy, int n, int red, int green, int blue, int alpha);
        //! Draw a Polygon with float RBGA colour values (0.0f-1.0f)
        virtual void polygonRGBA(float* vx, float* vy, int n, float red, float green, float blue, float alpha);
        //! Draw a Polygon with Colour (where colours components are floats)
        virtual void polygonColour(float* vx, float* vy, int n, Colour colour);
        //! Draw a Filled Polygon with int RBGA colour values (0-255)
        virtual void filledPolygonRGBA(float* vx, float* vy, int n, int red, int green, int blue, int alpha);
        //! Draw a Filled Polygon with float RBGA colour values (0.0f-1.0f)
        virtual void filledPolygonRGBA(float* vx, float* vy, int n, float red, float green, float blue, float alpha);
        //! Draw a Filled Polygon with Colour (where colours components are floats)
        virtual void filledPolygonColour(float* vx, float* vy, int n, Colour colour);

    // TEXTURES
    public:
        //! Enable Texture
        virtual void enableTexture();
        //! Disable Texture
        virtual void disableTexture();
        //! Set Texture
        virtual void setTexture(unsigned int textureID);

    // BLENDMODE
    public:
        //! Enable Blending
        virtual void enableBlending();
        //! Disable Blending
        virtual void disableBlending();
        //! Set BlendMode
        virtual void setBlendMode(int sFactor, int gFactor);

    // STIPPLE
    public:
        //! Enable Stipple
        virtual void enableStipple();
        //! Disable Stipple
        virtual void disableStipple();
        //! Set Line Stipple
        virtual void setLineStipple(int factor, unsigned short pattern);

    protected:
        // Methods and Members

/*
    // ***************
    // * LUABINDINGS *
    // ***************
    public:
        //! Bind this class to a luaState
        static void bindToLua(lua_State* pLuaState);
*/
};

#endif // OPENGLDRAW_H
