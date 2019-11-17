#include "Camera3D.h"

Camera3D::Camera3D()
{
    // Set running Flag
    this->runningFlag = false;
    // Set paused Flag
    this->pausedFlag = false;
    // Transform
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->xVelocity = 0.0f;
    this->yVelocity = 0;
    this->zVelocity = 0;
    this->xAcceleration = 0.0f;
    this->yAcceleration = 0.0f;
    this->zAcceleration = 0.0f;
    this->pitch = 0.0f;
    this->yaw = 0.0f;
    this->roll = 0.0f;
    // TODO: Up, Forward vectors
    // Dimensions
    this->viewPortWidth = 640.0f;
    this->viewPortHeight = 480.0f;
    // Perspective Matrix stuff
    this->fovy = 45.0f;
    this->aspect = this->viewPortHeight / this->viewPortWidth;
    this->zNear = 1.0f;
    this->zFar = 100000.0f;
    // Bound to a region Flag
    this->boundFlag = false;
    this->boundX = 0.0f;
    this->boundY = 0.0f;
    this->boundZ = 0.0f;
    this->boundWidth = 0.0f;
    this->boundHeight = 0.0f;
    this->boundDepth = 0.0f;
    // Shake
    this->shaking = false;
    this->shakeX = 1.0f;
    this->shakeY = 1.0f;
    this->shakeZ = 1.0f;
}

Camera3D::~Camera3D()
{

}

//Camera3D::Camera3D(const Camera3D& other)
//{
//
//}

bool Camera3D::init()
{
    // Swap to the Project matrix
    glMatrixMode(GL_PROJECTION);
    // Reset the Projection Matrix
    glLoadIdentity();
    // TODO: legacy get rid of this
    //// Populate thee current matrix with a projection matrix
    //glOrtho(0, this->viewPortWidth, this->viewPortHeight, 0, 1, -1);
    // Populate thee current matrix with a projection matrix
    gluPerspective(this->fovy, this->aspect, this->zNear, this->zNear);
    // Camera successfully initialised
    return true;
}

void Camera3D::update(float dTime)
{
    this->xAcceleration += this->xVelocity;
    this->yAcceleration += this->yVelocity;
    this->zAcceleration += this->zVelocity;
    this->x += this->xVelocity;
    this->y += this->yVelocity;
    this->z += this->zVelocity;
}

void Camera3D::draw()
{
    // Swap to the Project matrix
    glMatrixMode(GL_PROJECTION);
    // Reset the Projection Matrix
    glLoadIdentity();
    // Populate thee current matrix with a projection matrix
    gluPerspective(this->fovy, this->aspect, this->zNear, this->zNear);
    // TODO: replace gluOrtho with gluPerspective()
    if (this->shaking == true)
    {
        // Make the screen shake
        glTranslatef(((float)rand() / (float)RAND_MAX - (float)rand() / (float)RAND_MAX) * this->shakeX, ((float)rand() / (float)RAND_MAX - (float)rand() / (float)RAND_MAX) * this->shakeY, 0.0f);
    }
    // Swap to the Modelview matrix
    glMatrixMode(GL_MODELVIEW);
}

void Camera3D::free()
{
    // Transform
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->xVelocity = 0;
    this->yVelocity = 0;
    this->zVelocity = 0;
    this->xAcceleration = 0.0f;
    this->yAcceleration = 0.0f;
    this->zAcceleration = 0.0f;
    this->pitch = 0.0f;
    this->yaw = 0.0f;
    this->roll = 0.0f;
    // TODO: Up, Forward vectors
    // Dimensions
    this->viewPortWidth = 640.0f;
    this->viewPortHeight = 480.0f;
    // Perspective Matrix stuff
    this->fovy = 45.0f;
    this->aspect = this->viewPortHeight / this->viewPortWidth;
    this->zNear = 1.0f;
    this->zFar = 100000.0f;
    // Bound to a region Flag
    this->boundFlag = false;
    this->boundX = 0.0f;
    this->boundY = 0.0f;
    this->boundZ = 0.0f;
    this->boundWidth = 0.0f;
    this->boundHeight = 0.0f;
    this->boundDepth = 0.0f;
    // Shake
    this->shaking = false;
    this->shakeX = 1.0f;
    this->shakeY = 1.0f;
    this->shakeZ = 1.0f;
}

void Camera3D::start()
{
    // Set running Flag
    this->runningFlag = true;
    // Set paused Flag
    this->pausedFlag = false;
}

void Camera3D::stop()
{
    // Set running Flag
    this->runningFlag = false;
    // Set running Flag
    this->runningFlag = false;
}

void Camera3D::pause()
{
    // Set paused Flag
    this->pausedFlag = true;
}

void Camera3D::resume()
{
    // Set paused Flag
    this->pausedFlag = false;
}

void Camera3D::reset()
{
    // Set running Flag
    this->runningFlag = false;
    // Set paused Flag
    this->pausedFlag = false;
}

void Camera3D::setPerspective(float fovy, float aspect, float zNear, float zFar)
{
    gluPerspective(this->fovy, this->aspect, this->zNear, this->zNear);
}

void Camera3D::startShake()
{
    this->shaking = true;
}

void Camera3D::stopShake()
{
    this->shaking = false;
}

void Camera3D::shake()
{

}
