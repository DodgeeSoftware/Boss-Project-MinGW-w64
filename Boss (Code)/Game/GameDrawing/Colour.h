#ifndef COLOUR_H
#define COLOUR_H

// C++ Includes
#include <cmath>

/** The Colour class is a simple wrapper around 4 floats representing an RBGA colour
    in the range of 0.0f - 1.0f **/
class Colour
{
    // ******************************
    // * CONSTRUCTORS / DESTRUCTORS *
    // ******************************
    public:
        //! Constructor
        Colour()
        {
            // Default Colour Components
            this->red = 0.0f;
            this->green = 0.0f;
            this->blue = 0.0f;
            this->alpha = 1.0f;

//            this->YELLOW =
//            this->OLIVE =
//            this->LIME =
//            this->GREEN =
//            this->AQUA =
//            this->TEAL =
//            this->BLUE =
//            this->NAVY =
//            this->FUCHSIA =
//            this->PURPLE =
        }
        //! Constructor
        Colour(float red, float green, float blue, float alpha)
        {
            this->red = red;
            this->green = green;
            this->blue = blue;
            this->alpha = alpha;
        }
        //! Destructor
        virtual ~Colour() {}

    protected:
        // No functions

    // ************************
    // * OVERLOADED OPERATORS *
    // ************************
    public:
        //! Overloaded assignment operator
        Colour operator=(const Colour& colour);
        //! Overloaded addition operator
        Colour operator+(const Colour& colour);
        //! Overloaded subtraction operator
        Colour operator-(const Colour& colour);
        //! Overloaded multiplication operator
        Colour operator*(const float& scalar);
        //! Overloaded division operator
        Colour operator/(const float& scalar);
        //! Overloaded equality operator
        bool operator==(const Colour& colour);
        //! Overloaded not operator
        bool operator!=(const Colour& colour);

    protected:
        // No functions

    // ********************
    // * COLOUR FUNCTIONS *
    // ********************
    public:
        //! Normalise the Colour
        virtual void normalise();
        //! Return what this Colour would be if it were normalised
        virtual Colour normalised();
        //! Return the magnitude of this vector
        virtual float magnitude();
        //! Set Colour
        virtual void setColour(float red, float green, float blue, float alpha)
        {
            this->red = red;
            this->green = green;
            this->blue = blue;
            this->alpha = alpha;
        }

    // *********************
    // * COLOUR COMPONENTS *
    // *********************
    public:
        // Red colour component
        float red;
        // Green colour component
        float green;
        // Blue colour component
        float blue;
        // Alpha colour component
        float alpha;

    // ******************
    // * COLOUR PRESETS *
    // ******************
    public:
        //! White
        static const Colour& WHITE;
        //! Silver
        static const Colour& SILVER;
        //! Gray
        static const Colour& GRAY;
        //! Black
        static const Colour& BLACK;
        //! Red
        static const Colour& RED;
        //! Maroon
        static const Colour& MAROON;
        //! Yellow
        static const Colour& YELLOW;
        //! Olive
        static const Colour& OLIVE;
        //! Lime
        static const Colour& LIME;
        //! Green
        static const Colour& GREEN;
        //! Aqua
        static const Colour& AQUA;
        //! Teal
        static const Colour& TEAL;
        //! Blue
        static const Colour& BLUE;
        //! Navy
        static const Colour& NAVY;
        //! Fuchsia
        static const Colour& FUCHSIA;
        //! Purple
        static const Colour& PURPLE;

/*
    // ****************
    // * LUA BINDINGS *
    // ****************
    public:
        //! Bind this class to a luaState
        static void bindToLua(lua_State* pLuaState);
*/
};

#endif //  COLOUR_H
