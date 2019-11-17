#include "Colour.h"

void Colour::normalise()
{
    if (this->magnitude() != 0)
    {
        // normalise this colour
        this->red = this->red / this->magnitude();
        this->green = this->green / this->magnitude();
        this->blue = this->blue / this->magnitude();
    }
}

Colour Colour::normalised()
{
    // return a normalised copy of this colour
    return (this->magnitude() != 0) ? Colour(this->red / this->magnitude(), this->green / this->magnitude(), this->blue / this->magnitude(), this->alpha) : Colour();
}

float Colour::magnitude()
{
    // length of the the colour
    return sqrtf(this->red * this->red + this->green * this->green + this->blue * this->blue + 0.0f * this->alpha * this->alpha); // Design Choice, I didnt want alpha to affect the length of the colour
}

Colour Colour::operator=(const Colour& colour)
{
    this->red = colour.red;
    this->green = colour.green;
    this->blue = colour.blue;
    this->alpha = colour.alpha;
    return (*this);
}

Colour Colour::operator+(const Colour& colour)
{
    this->red += colour.red;
    this->green += colour.green;
    this->blue += colour.blue;
    this->alpha += colour.alpha;
    return (*this);
}

Colour Colour::operator-(const Colour& colour)
{
    this->red -= colour.red;
    this->green -= colour.green;
    this->blue -= colour.blue;
    this->alpha -= colour.alpha;
    return (*this);
}

Colour Colour::operator*(const float& value)
{
    this->red *= value;
    this->green *= value;
    this->blue *= value;
    this->alpha *= value;
    return (*this);
}

Colour Colour::operator/(const float& value)
{
    this->red /= value;
    this->green /= value;
    this->blue /= value;
    this->alpha /= value;
    return (*this);
}

bool Colour::operator==(const Colour& colour)
{
    return ((this->red == colour.red) && (this->green == colour.green) && (this->green == colour.blue) && (this->alpha == colour.alpha));
}

bool Colour::operator!=(const Colour& colour)
{
    return ((this->red != colour.red) || (this->green != colour.green) || (this->green != colour.blue) || (this->alpha != colour.alpha));
}

// Colour Presets
const Colour& Colour::WHITE = Colour(1.0f, 1.0f, 1.0f, 1.0f);;
const Colour& Colour::SILVER = Colour(0.75f, 0.75f, 0.75f, 1.0f);
const Colour& Colour::GRAY = Colour(0.5f, 0.5f, 0.5f, 1.0f);
const Colour& Colour::BLACK = Colour(0.0f, 0.0f, 0.0f, 1.0f);
const Colour& Colour::RED = Colour(1.0f, 0.0f, 0.0f, 1.0f);
const Colour& Colour::MAROON = Colour(0.5f, 0.0f, 0.0f, 1.0f);
const Colour& Colour::YELLOW = Colour(1.0f, 1.0f, 0.0f, 1.0f);
const Colour& Colour::OLIVE = Colour(0.5f, 0.5f, 0.0f, 1.0f);
const Colour& Colour::LIME = Colour(0.0f, 1.0f, 0.0f, 1.0f);
const Colour& Colour::GREEN = Colour(0.0f, 0.5f, 0.0f, 1.0f);
const Colour& Colour::AQUA = Colour(0.0f, 1.0f, 1.0f, 1.0f);
const Colour& Colour::TEAL = Colour(0.0f, 0.5f, 0.5f, 1.0f);
const Colour& Colour::BLUE = Colour(0.0f, 0.0f, 1.0f, 1.0f);
const Colour& Colour::NAVY = Colour(0.0f, 1.0f, 0.5f, 1.0f);
const Colour& Colour::FUCHSIA = Colour(1.0f, 0.0f, 1.0f, 1.0f);
const Colour& Colour::PURPLE = Colour(0.5f, 0.0f, 0.5f, 1.0f);

/*
void Colour::bindToLua(lua_State* pLuaState)
{
    // Bind functions to lua state
    luabind::module(pLuaState)
    [
        luabind::class_<Colour>("Colour")
        .def(luabind::constructor<>())
        .def(luabind::constructor<float, float, float, float>())
        .def("normalise", (void (Colour::*)()) &Colour::normalise)
        .def("normalised", (Colour (Colour::*)()) &Colour::normalised)
        .def("magnitude", (float (Colour::*)(float)) &Colour::magnitude)
        // Assignment Operator Overloading is not supported by lua and for good reason (script locals could accidently be assigned program addresses *nods* )
        .def(luabind::self + Colour())
        .def(luabind::self - Colour())
        .def(luabind::self * float())
        .def(luabind::self / float())
        //.def(luabind::self == Colour())
        //.def(luabind::self != Colour())
        .def_readwrite("red", &Colour::red)
        .def_readwrite("green", &Colour::green)
        .def_readwrite("blue", &Colour::blue)
        .def_readwrite("alpha", &Colour::alpha)

        .def_readwrite("r", &Colour::red)
        .def_readwrite("g", &Colour::green)
        .def_readwrite("b", &Colour::blue)
        .def_readwrite("a", &Colour::alpha)

        // TODO: More bindings
        // TODO: Binding Static Members Colours is going to be alittle difficult :(
    ];
}
*/
