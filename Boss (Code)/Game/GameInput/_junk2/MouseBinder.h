#ifndef MOUSEBINDER_H
#define MOUSEBINDER_H

#include <map>

/* NOTE: this class may end up forcing alittle redesign of the input system
    the present design doesnt support bindings. It currently used real word queries
    such as is mouse down rather than querying specific button state info from sdl
    An alternative is to expose the sdl button state and then query that to apply
    mapping */
// TODO: Build Me
class MouseBinder
{
    public:
        //! Default Constructor
        MouseBinder()
        {

        }
        //! Destructor
        virtual ~MouseBinder() {}

    private:
        //std::map<char*,
};

#endif // MOUSEBINDER_H
