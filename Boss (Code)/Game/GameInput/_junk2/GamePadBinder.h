#ifndef GAMEPADBINDER_H
#define GAMEPADBINDER_H

#include <climits>
#include <map>

// TODO: This binder will need to deal with multiple game pads and doesn't right now :(
class GamePadBinder
{
    public:
        //! Default Constructor
        GamePadBinder()
        {

        }
        //! Destructor
        virtual ~GamePadBinder() {}

    public:
        //! Add a binding to a button
        void addButtonBinding(char* name, int button);
        //! Remove a button binding
        void removeButtonBinding(char* name);
        //! Get a button binding
        int getButton(char* name);
        //! Is there a button binding
        bool isButtonBinding(char* name);

    public:
        //! Add a binding to an axis
        void addAxisBinding(char* name, int axis);
        //! Remove an axis binding
        void removeAxisBinding(char* name);
        //! Get an axis binding
        int getAxis(char* name);
        //! Is there an axis binding
        bool isAxisBinding(char* name);

    public:
        //! Clear GamePad bindings
        void clear();

    private:
        // Map of GamePad buttons
        std::map<char*, int> buttonMap;
        // Map of GamePad axes
        std::map<char*, int> axisMap;
};

#endif // GAMEPADBINDER_H
