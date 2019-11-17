#ifndef ICAMERA_H
#define ICAMERA_H

/** The ICamera class is a pure abstract class which defines the interface
    for a Game Camera **/
class ICamera
{
    // *****************************
    // * CONSTRUCTORS / DESTRUCTOR *
    // *****************************
    public:
        //! Default Constructor
        ICamera()
        {
            this->viewPortWidth = 0.0f;
            this->viewPortHeight = 0.0f;
        }
        //! Destructor
        virtual ~ICamera() {}

    protected:
        // No functions or members

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************
    public:
        //! Initilise the camera
        virtual bool init() = 0;
        //! Interpolate the camera to the next frame
        virtual void update(float dTime) = 0;
        //! Set the viewport for drawing
        virtual void draw() = 0;
        //! Free the camera
        virtual void free() = 0;

    protected:
        // no functions or members

    // *************
    // * VIEW PORT *
    // *************
    public:
        //! Get Viewport Width
        virtual float getViewPortWidth() { return this->viewPortWidth; }
        //! Get Viewport Height
        virtual float getViewPortHeight() { return this->viewPortHeight; }
        //! Set Viewport Width
        virtual void setViewPortWidth(float viewPortWidth) { this->viewPortWidth = viewPortWidth; }
        //! Set Viewport Height
        virtual void setViewPortHeight(float viewPortHeight) { this->viewPortHeight = viewPortHeight; }

    protected:
        // Viewport width
        float viewPortWidth;
        // Viewport height
        float viewPortHeight;
};

#endif // ICAMERA_H
