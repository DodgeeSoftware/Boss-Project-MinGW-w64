#include "Camera2D.h"

Camera2D::Camera2D()
{
    // Set running Flag
    this->runningFlag = false;
    // Set paused Flag
    this->pausedFlag = false;
    // Position
    this->x = 0;
    this->y = 0;
    // Velocity
    this->xVelocity = 0.0f;
    this->yVelocity = 0.0f;
    // Acceleration
    this->xAcceleration = 0.0f;
    this->yAcceleration = 0.0f;
    // Dimensions
    this->viewPortWidth = 0;
    this->viewPortHeight = 0;
    // Bound to a region Flag
    this->boundFlag = false;
    this->boundX = 0.0f;
    this->boundY = 0.0f;
    this->boundWidth = 0.0f;
    this->boundHeight = 0.0f;
    // Zoom
    this->zoom = 1.0f;
    this->zoomFocusX = 0.0f;
    this->zoomFocusY = 0.0f;
    // Shake
    this->shaking = false;
    this->shakeX = 1.0f;
    this->shakeY = 1.0f;
}

Camera2D::~Camera2D()
{

}

//Camera2D::Camera2D(const Camera2D& other)
//{
//
//}

bool Camera2D::init()
{
    // Swap to the Project Matrix
    glMatrixMode(GL_PROJECTION);
    // Reset the Projection Matrix
    glLoadIdentity();
    // Populate thee current matrix with a projection matrix
    glOrtho(0, this->viewPortWidth, this->viewPortHeight, 0.0, 1.0, -1.0);
    // Swap to the ModelView Matrix
    glMatrixMode(GL_MODELVIEW);
    // Reset the ModelView Matrix
    glLoadIdentity();
    // Camera successfully initialised
    return true;
}

void Camera2D::update(float dTime)
{
    this->xVelocity += this->xAcceleration;
    this->yVelocity += this->yAcceleration;
    this->x += this->xVelocity;
    this->y += this->yVelocity;
}

void Camera2D::draw()
{
    // Swap to the Project matrix
    glMatrixMode(GL_PROJECTION);
    // Reset the Projection Matrix
    glLoadIdentity();
    // Populate thee current matrix with a projection matrix
    glOrtho(0, this->viewPortWidth, this->viewPortHeight, 0.0, 0.0, 1.0);
    if (this->shaking == true)
    {
        // Make the screen shake
        glTranslatef(((float)rand() / (float)RAND_MAX - (float)rand() / (float)RAND_MAX) * this->shakeX, ((float)rand() / (float)RAND_MAX - (float)rand() / (float)RAND_MAX) * this->shakeY, 0.0f);
    }
    // Restore the position of the camera
    glTranslatef(this->zoomFocusX, this->zoomFocusY, 0.0f);
    // Set the scale (not the same az zoom but similar results)
    glScalef(this->zoom, this->zoom, 1.0f);
    // Make the Centre of the camera the origin for zooming
    glTranslatef(-this->zoomFocusX, -this->zoomFocusY, 0.0f);
    // Swap to the Modelview matrix
    glMatrixMode(GL_MODELVIEW);
}

void Camera2D::clear()
{
    // Position
    this->x = 0;
    this->y = 0;
    // Velocity
    this->xVelocity = 0.0f;
    this->yVelocity = 0.0f;
    // Acceleration
    this->xAcceleration = 0.0f;
    this->yAcceleration = 0.0f;
    // Dimensions
    this->viewPortWidth = 0;
    this->viewPortHeight = 0;
    // Bound to a region Flag
    this->boundFlag = false;
    this->boundX = 0.0f;
    this->boundY = 0.0f;
    this->boundWidth = 0.0f;
    this->boundHeight = 0.0f;
    // Zoom
    this->zoom = 1.0f;
    this->zoomFocusX = 0.0f;
    this->zoomFocusY = 0.0f;
    // Shake
    this->shaking = false;
    this->shakeX = 1.0f;
    this->shakeY = 1.0f;
}

void Camera2D::free()
{
    // Position
    this->x = 0;
    this->y = 0;
    // Velocity
    this->xVelocity = 0.0f;
    this->yVelocity = 0.0f;
    // Acceleration
    this->xAcceleration = 0.0f;
    this->yAcceleration = 0.0f;
    // Dimensions
    this->viewPortWidth = 0;
    this->viewPortHeight = 0;
    // Bound to a region Flag
    this->boundFlag = false;
    this->boundX = 0.0f;
    this->boundY = 0.0f;
    this->boundWidth = 0.0f;
    this->boundHeight = 0.0f;
    // Zoom
    this->zoom = 1.0f;
    this->zoomFocusX = 0.0f;
    this->zoomFocusY = 0.0f;
    // Shake
    this->shaking = false;
    this->shakeX = 1.0f;
    this->shakeY = 1.0f;
}

void Camera2D::start()
{
    // Set running Flag
    this->runningFlag = true;
}

void Camera2D::stop()
{
    // Set running Flag
    this->runningFlag = false;
}

void Camera2D::pause()
{
    // Set paused Flag
    this->pausedFlag = true;
}

void Camera2D::resume()
{
    // Set paused Flag
    this->pausedFlag = false;
}

void Camera2D::reset()
{
    // Position
    this->x = 0;
    this->y = 0;
    // Velocity
    this->xVelocity = 0.0f;
    this->yVelocity = 0.0f;
    this->xAcceleration = 0.0f;
    this->yAcceleration = 0.0f;
    //// Dimensions
    //this->viewPortWidth = 0;
    //this->viewPortHeight = 0;
    // Bound to a region Flag
    //this->boundFlag = false;
    //this->boundX = 0.0f;
    //this->boundY = 0.0f;
    //this->boundWidth = 0.0f;
    //this->boundHeight = 0.0f;
    // Zoom
    this->zoom = 1.0f;
    //this->zoomFocusX = 0.0f;
    //this->zoomFocusY = 0.0f;
    // Shake
    this->shaking = false;
    this->shakeX = 1.0f;
    this->shakeY = 1.0f;
}

void Camera2D::startShake()
{
    this->shaking = true;
}

void Camera2D::stopShake()
{
    this->shaking = false;
}

void Camera2D::setShakeBounds(float shakeX, float shakeY)
{
    this->shakeX = shakeX;
    this->shakeY = shakeY;
}

void Camera2D::shake()
{
    // TODO: Implement me
}
