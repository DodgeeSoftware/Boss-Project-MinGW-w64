#include "Game.h"

/* LuaBindings (this must be the last include)
    classes that come before this must be
    defined before we can bind them */
#include "GameLuaBindings.h"

Game* Game::pInstance = NULL;

Game::Game()
{
    // **************
    // * GAME STATE *
    // **************

    this->pGameState = 0;

    // ******************
    // * RUNNING/PAUSED *
    // ******************

    this->running = false;
    this->paused = false;

    // ****************
    // * FRAMELIMITER *
    // ****************

    this->now = 0;
    this->then = 0;
    this->accumulator = 0;
    this->desiredFPS = 60.0f;
    this->limitFramesPerSecond = true;

    // ********************
    // * APPLICATION TIME *
    // ********************

    this->applicationTimer.stop();
    this->applicationTicks = 0.0f;
}

Game::~Game()
{

}

Game* Game::getInstance()
{
    /* if there is no instance of the game class
       then create one. */
    if (Game::pInstance == 0)
    {
        // create an instance of the Game class
        Game::pInstance = new Game();
    }
    // return the instance of the game engine class
    return Game::pInstance;
}

int Game::run(int argc, char *argv[])
{
    // *******
    // * RUN *
    // *******

    // Initialise and run the game
    if (this->init() == true)
    {
        // Start the engine
        this->start();
        // While the is Running flag is true keep running
        while (this->isRunning() == true)
        {
            // Grab applicaitonTicks
            this->applicationTicks = this->applicationTimer.getTicks();
            // If the frame rate limiter is on, limit the frame rate otherwise dont
            if (this->limitFramesPerSecond == true)
            {
                // Frame Rate Limiter
                this->then = this->now;
                this->now = (float)this->frameTimer.getTicks() / 1000.0f;
                this->accumulator += ((float)this->now - (float)this->then);
                // Loop until we have caught up
                while(this->accumulator > (1.0f / this->desiredFPS))
                {
                    // Handle events such as keypresses, mouse movements and gamepad input
                    this->handleEvents();
                    // Process logic
                    this->think();
                    // Update
                    this->update();
                    // Draw all graphics
                    this->draw();
                    // Draw all graphics
                    this->drawGUI();
                    // Swapbuffers
                    this->swapBuffers();
                    /* keep decreasting the accumulator until the frame has
                        caught up to the desired FPS */
                    this->accumulator -= (1.0f / this->desiredFPS);
                }
            }
            else
            {
                // Handle events such as keypressses, mouse movements and gamepad input
                this->handleEvents();
                // Process logic
                this->think();
                // Update
                this->update();
                // Draw all graphics
                this->draw();
                // Draw all graphics
                this->drawGUI();
                // Swapbuffers
                this->swapBuffers();
            }
        }
        // Stop the engine
        this->stop();
    }
    // Shut Everything down
    this->quit();

    system("pause");

    // Program successfully executed
    return EXIT_SUCCESS;
}

bool Game::init()
{
    // ********
    // * INIT *
    // ********

    // send a message to the console
    std::cout << "Game::init()" << std::endl;
    // Send Engine Version information to the console
    std::cout << "GLFW Version: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;
    // Send a message to the console
    std::cout << "glfwInit" << std::endl;
    // Initialise GLFW
    if (glfwInit() == GL_TRUE)
    {
        // Set the GLFW error handling callback
        glfwSetErrorCallback(Game::GLFWErrorCallback);
        // Send a message to the console
        std::cout << "glfwInit Success." << std::endl;
    }
    else
    {
        // Send a message to the console
        std::cout << "ERROR: glfwInit Failed." << std::endl;
        // Initialising glfwInit Failed
        return false;
    }

    // Init the config
    if (this->initConfig() == false)
        return false;
    // Init the game window
    if (this->initWindow() == false)
        return false;
    // Init the input system
    if (this->initInputSystem() == false)
        return false;
    // Init the game audio library
    if (this->initAudio() == false)
        return false;
    // Init the game font library
    if (this->initText() == false)
        return false;
    // Init the view port
    if (this->initCamera() == false)
        return false;

    // Seed random number generator
    srand(time(NULL));

    // send a message to the console
    std::cout << "Game::init() Success" << std::endl;

    // Game Init was successful
    return true;
}

bool Game::initConfig()
{
    // ***************
    // * INIT CONFIG *
    // ***************

    // send a message to the console
    std::cout << "Game::initConfig()" << std::endl;

    // Configuration filename
    if (this->config.load(Globals::configurationFilename) == false)
    {
        // failure
        return false;
    }
    // Send the Config to the console
    this->config.toConsole();

    // send a message to the console
    std::cout << "Game::initConfig() Success" << std::endl;

    // Game Init config successful
    return true;
}

bool Game::initWindow()
{
    // ***************
    // * INIT WINDOW *
    // ***************

    std::cout << "Game::initWindow()" << std::endl;

    // Does the window have a border and a close button
    //glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    glfwWindowHint(GLFW_DECORATED, GL_TRUE);
    // Make the window the focus of input
    glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
    //// Make the window not iconified
    //glfwWindowHint(GLFW_ICONIFIED, GL_FALSE);
    // Make the window unresizable
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // Make the window Visible
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
    // Don't Automatically Iconify When Focus is lost
    glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);

    // Create the Game Window
    this->pWindow = glfwCreateWindow(this->config.getWidth(), this->config.getHeight(), "", 0, 0);
    // Handle problems making a window
    if (this->pWindow == 0)
    {
        // Failed to create the application window
        return false;
    }
    // Make the window context current
    glfwMakeContextCurrent(this->pWindow);

    // Set the GLFW window callbacks
    this->setWindowCallBacks();

    // send a message to the console
    std::cout << "Game::initWindow() Success" << std::endl;

    // Window successfully created
    return true;
}

bool Game::initInputSystem()
{
    // *********************
    // * INIT INPUT SYSTEM *
    // *********************

    // send a message to the console
    std::cout << "Game::initInputSystem()" << std::endl;

    // Set the window handle for the input system
    this->inputSystem.setWindow(this->pWindow);
    // Initialise input system
    if (this->inputSystem.init() == false)
    {
        // send a message to the console
        std::cout << "ERROR: Failed to initialise input system" << std::endl;
        // Failed to Initialise input system
        return false;
    }
    // Show the cursor
    this->getInputSystem()->getMouse()->setVisibility(true);
    // Set GLFW Keyboard Callbacks
    glfwSetKeyCallback(this->pWindow, Game::keyFunction);
    glfwSetCharCallback(this->pWindow, Game::charFunction);
    // Set GLFW Mouse Callbacks
    glfwSetMouseButtonCallback(this->pWindow, Game::mouseButtonFunction);
    glfwSetCursorPosCallback(this->pWindow, Game::cursorPositionFunction);
    glfwSetCursorEnterCallback(this->pWindow, Game::cursorEnterFunction);
    glfwSetScrollCallback(this->pWindow, Game::scrollFunction);
    // Set GLFW GamePad Callbacks
    glfwSetJoystickCallback(Game::gamePadFunction);

    // send a message to the console
    std::cout << "Game::initInputSystem() Success" << std::endl;

    // Successfully initialised the input system
    return true;
}

bool Game::initAudio()
{
    // **************
    // * INIT AUDIO *
    // **************

    // send a message to the console
    std::cout << "Game::initAudio()" << std::endl;

    // TODO: Initialise FMOD here

    // send a message to the console
    std::cout << "Game::initAudio() Success" << std::endl;

    return true;
}

bool Game::initText()
{
    // *************
    // * INIT TEXT *
    // *************

    // Send a message to the console
    std::cout << "Game::initText()" << std::endl;

    // TODO: Initialise FreeType2 here

    // Send a message to the console
    std::cout << "Game::initText() Success" << std::endl;

    return true;
}

bool Game::initCamera()
{
    // ***************
    // * INIT CAMERA *
    // ***************

    // Send a message to the console
    std::cout << "Game::initCamera()" << std::endl;

    // CAMERA2D
    // Set default camera horizontal position
    this->camera2D.setX(0.0f);
    // Set default camera vertical position
    this->camera2D.setY(0.0f);
    // Set Zoom
    this->camera2D.setZoom(1.0f);
    // Set default viewport width
    this->camera2D.setViewPortWidth(this->config.getWidth());
    // Set default viewport height
    this->camera2D.setViewPortHeight(this->config.getHeight());
    // Set up the projection matrix
    this->camera2D.draw();

    // Send a message to the console
    std::cout << "Game::initCamera() Success" << std::endl;

    // Camera setup successfully
    return true;
}

void Game::handleEvents()
{
    // *****************
    // * HANDLE EVENTS *
    // *****************

    // Handle window close events
    if (glfwWindowShouldClose(this->pWindow))
    {
        // Set Running
        this->setRunning(false);
        // Return
        return;
    }
    // Pass events to the input system
    this->inputSystem.handleEvents();
    // HandleEvents for the Game State
    if (this->pGameState != 0)
        this->pGameState->handleEvents();
}

void Game::think()
{
    // *********
    // * THINK *
    // *********

    // Think for the Game State
    if (this->pGameState != 0)
        this->pGameState->think();
}

void Game::update()
{
    // **********
    // * UPDATE *
    // **********

    // Update for the Game State
    if (this->pGameState != 0)
        this->pGameState->update();
    // Update input system
    this->inputSystem.update();
    // Clear events from the message queue (clears the message stack in windows so is handled last)
    glfwPollEvents();
}

void Game::draw()
{
    // ********
    // * DRAW *
    // ********

    if (this->clearColour[3] > 0.0f)
    {
        // Set the Clear colour
        glClearColor(this->clearColour[0], this->clearColour[1], this->clearColour[2], this->clearColour[3]);
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
    }
    // Clear the screen
    glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    // Update the renders per second
    this->rpsCounter.update();
    // build the view port
    this->camera2D.draw();
    // Swap to the model view matrix and  it
    glMatrixMode(GL_MODELVIEW);
    //  the Modelview Matrix
    glLoadIdentity();
    // Draw the GameState
    if (this->pGameState != 0)
        this->pGameState->draw();
}

void Game::drawGUI()
{
    // ***********
    // * DRAWGUI *
    // ***********

    // Swap to the Project matrix
    glMatrixMode(GL_PROJECTION);
    //  the Projection Matrix
    glLoadIdentity();
    // Populate thee current matrix with a projection matrix
    glOrtho(0, this->config.getWidth(), this->config.getHeight(), 0, 1, -1);
    // Swap to the Modelview matrix
    glMatrixMode(GL_MODELVIEW);
    // If there is a state draw the GUI
    if (this->pGameState != 0)
        this->pGameState->drawGUI();
}

void Game::swapBuffers()
{
    // Swap the back buffer to the front (double buffered OpenGL Context)
    glfwSwapBuffers(this->pWindow);
}

void Game::quit()
{
    // ********
    // * QUIT *
    // ********

    // send a message to the console
    std::cout << "Game::quit()" << std::endl;

    // Shutdown the camera
    this->shutdownCamera();
    // Shutdown InputSystem
    this->shutdownInputSystem();
        // Shutdown the audio
    this->shutdownAudio();
    // Shutdown the Font
    this->shutdownFont();
    // Shutdown Window
    this->shutdownWindow();
    // Shutdown Config
    this->shutdownConfig();

    // send a message to the console
    std::cout << "Game::quit() success" << std::endl;
}

void Game::shutdownCamera()
{
    // send a message to the console
    std::cout << "Game::shutdownCamera()" << std::endl;

    // release the camera
    this->camera2D.free();

    // send a message to the console
    std::cout << "Game::shutdownCamera() Success" << std::endl;
}

void Game::shutdownInputSystem()
{
    // send a message to the console
    std::cout << "void Game::shutdownInputSystem()" << std::endl;

    // Free the input system
    this->inputSystem.free();

    // send a message to the console
    std::cout << "void Game::shutdownInputSystem() Success" << std::endl;
}

void Game::shutdownWindow()
{
    // send a message to the console
    std::cout << "Game::shutdownWindow()" << std::endl;

    // Destroy the game window
    glfwDestroyWindow(this->pWindow);
    this->pWindow = 0;

    // send a message to the console
    std::cout << "Game::shutdownWindow() Success" << std::endl;
}

void Game::shutdownAudio()
{
    // send a message to the console
    std::cout << "Game::shutdownAudio()" << std::endl;

    // send a message to the console
    std::cout << "Game::shutdownAudio() Success" << std::endl;
}

void Game::shutdownFont()
{
    // send a message to the console
    std::cout << "Game::shutdownFont()" << std::endl;

    // send a message to the console
    std::cout << "Game::shutdownFont() Success" << std::endl;
}

void Game::shutdownConfig()
{
    // send a message to the console
    std::cout << "Game::shutdownConfig()" << std::endl;

    // Clear Config
    this->config.clear();

    // send a message to the console
    std::cout << "Game::shutdownConfig() Success" << std::endl;
}

void Game::setWindowCallBacks()
{
    glfwSetWindowPosCallback(this->pWindow, Game::windowRepositionCallback);
    glfwSetWindowSizeCallback(this->pWindow, Game::windowResizeCallback);
    glfwSetWindowCloseCallback(this->pWindow, Game::windowCloseCallback);
    glfwSetWindowRefreshCallback(this->pWindow, Game::windowRefreshCallback);
    glfwSetWindowFocusCallback(this->pWindow, Game::windowFocusChangeCallback);
    glfwSetWindowIconifyCallback(this->pWindow, Game::windowIconifyCallback);
}

void Game::windowRepositionCallback(GLFWwindow* pWindow, int newX, int newY)
{
    /* NOTE: this function captures the user repositioning the window */
    // if there is a state fire the Callback
    if (Game::getInstance()->getGameState() != 0)
        Game::getInstance()->getGameState()->onWindowReposition(newX, newY);
}

void Game::windowResizeCallback(GLFWwindow* pWindow, int newWidth, int newHeight)
{
    /* NOTE: This callback is triggered when the user tries to resize the window */
    // Set xResolution
    Game::getInstance()->xResolution = newWidth;
    // Set yResolution
    Game::getInstance()->yResolution = newHeight;
    // if there is a state fire the Callback
    if (Game::getInstance()->getGameState() != 0)
        Game::getInstance()->getGameState()->onWindowResize(newWidth, newHeight);
}

void Game::windowCloseCallback(GLFWwindow* pWindow)
{
    /* NOTE: This callback is triggered when the user clicks the close button */
    // if there is a state fire the Callback
    if (Game::getInstance()->getGameState() != 0)
        Game::getInstance()->getGameState()->onWindowClose();
}

void Game::windowRefreshCallback(GLFWwindow* pWindow)
{
    // NOTE: This callback is triggered when a window refresh request is made
    // if there is a state fire the Callback
    if (Game::getInstance()->getGameState() != 0)
        Game::getInstance()->getGameState()->onWindowRefresh();
}

void Game::windowFocusChangeCallback(GLFWwindow* pWindow, int state)
{
    // NOTE: This callback is triggered when the application window focus status changes
    // if there is a state fire the Callback
    if (Game::getInstance()->getGameState() != 0)
        Game::getInstance()->getGameState()->onWindowFocusChange(state);
}

void Game::windowIconifyCallback(GLFWwindow* pWindow, int state)
{
    /* NOTE: This callback is triggered when the window is minimised or restored
              Examples of things to do here are to pause the game,
              hault music, turn up/down sound system volume etc */
    // if there is a state fire the Callback
    if (Game::getInstance()->getGameState() != 0)
        Game::getInstance()->getGameState()->onWindowIconify(state);
}

void Game::GLFWErrorCallback(int errorCode, const char* description)
{
    // Send a message to the console
    std::cout << "ERROR: GLFW Error Code: " << errorCode << std::endl;
    std::cout << description << std::endl;
}

void Game::mouseButtonFunction(GLFWwindow* pWindow, int button, int action, int mods)
{
    // Grab the Game Instance
    Game* pGame = Game::getInstance();

    // If a button has been pushed, set the AnyButton
    if (action == GLFW_PRESS)
        pGame->inputSystem.getMouse()->setAnyButton(button);

    // Fire the onMouseButton Event
    pGame->getInputSystem()->onMouseButton(button, action, mods);
}

void Game::cursorPositionFunction(GLFWwindow* pWindow, double x, double y)
{
    // Grab the Game Instance
    Game* pGame = Game::getInstance();
    // Set the Mouse Position
    pGame->inputSystem.getMouse()->setPosition(x, y);
    // Fire the onMouseMove Event
    pGame->getInputSystem()->onMouseMove(x, y);
}

void Game::cursorEnterFunction(GLFWwindow* pWindow, int entered)
{
    // Grab the Game Instance
    Game* pGame = Game::getInstance();
    /* This function sets the cursor boundary
        crossing callback of the specified window,
        which is called when the cursor enters or
        leaves the client area of the window.
        entered = TRUE cursor when into the window
        entered = FALSE cursor left the window */

    // Fire the Mouse Entered Event
    pGame->getInputSystem()->onMouseEnter(entered);
}

void Game::scrollFunction(GLFWwindow* pWindow, double x, double y)
{
    // Grab the Game Instance
    Game* pGame = Game::getInstance();
    // Set Scroll Wheel x
    pGame->getInputSystem()->getMouse()->setScrollWheelX(x);
    // Set Scroll Wheel y
    pGame->getInputSystem()->getMouse()->setScrollWheelY(y);
    // Fire the Mouse Scroll Event
    pGame->getInputSystem()->onMouseScroll(x, y);
}

void Game::keyFunction(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
    // Grab the Game Instance
    Game* pGame = Game::getInstance();
    // 888888888 TODO: Review this behaviour
        // If we have pressed a key then set the AnyKey
        if (action == GLFW_PRESS)
            pGame->getInputSystem()->getKeyboard()->setAnyKey(key);
    // 888888888888

    // Fire the OnKey Event
    pGame->getInputSystem()->onKey(key, scancode, action, mods);
}

void Game::charFunction(GLFWwindow* pWindow, unsigned int codePoint)
{
    // Grab the Game Instance
    Game* pGame = Game::getInstance();
    /* This function sets the character
        callback of the specified window,
        which is called when a Unicode
        character is input. */

    // Fire the OnChar Event
    pGame->getInputSystem()->onChar(codePoint);
}

void Game::gamePadFunction(int gamePadID, int event)
{
    // Grab the Game Instance
    Game* pGame = Game::getInstance();

    /* GamePadID is the numerical number associated with the GamePad
        which triggered this event.When the user connects a device event is GLFW_CONNECTED
        and when the user disconnects a device event is GLFW_DISCONNECTED */
    /* TODO: When GamePads are added and removed this is where I want
        to add and remove gamepads from our Input system */

    // Fire the OnGamePad Event
    pGame->getInputSystem()->onGamePad(gamePadID, event);
}

bool Game::loadConfig()
{
    return this->config.load(Globals::configurationFilename);
}

bool Game::saveConfig()
{
    return this->config.save(Globals::configurationFilename);
}

void Game::resetConfig()
{
    // Clear Config
    this->config.clear();
}

void Game::useDefaultConfig()
{
    // Clear Config
    this->config.clear();
}

void Game::setApplicationIconSmall(std::string filename)
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        HWND hWnd = glfwGetWin32Window(this->pWindow);
        HICON hIconSmall = (HICON)LoadImage(0, _T(filename.c_str()), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
        SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSmall);
        #else
            #error "Game::setApplicationIconSmall() does not currently support non windows operating systems"
    #endif
    #ifdef __linux__ || _LINUX
        // TODO: Implement me
    #endif // __linux__
    #ifdef TARGET_OS_MAC || _MACOSX
        // TODO: Implement me
    #endif // TARGET_OS_MAC
    // Set Small Application Icon filename
    this->smallApplicationIcon = filename;

    /* TODO: Review this function
        GLFWimage images[2];
        images[0] = load_icon("my_icon.png");
        images[1] = load_icon("my_icon_small.png");
        glfwSetWindowIcon(window, 2, images); */
}

void Game::setApplicationIconBig(std::string filename)
{
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        HWND hWnd = glfwGetWin32Window(this->pWindow);
        HICON hIconBig = (HICON)LoadImage(0, _T(filename.c_str()), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
        SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIconBig);
        #else
            #error "Game::setApplicationIconBig() does not currently support non windows operating systems"
    #endif
    #ifdef __linux__ || _LINUX
        // TODO: Implement me
        Display* pDisplay = glfwGetX11Display();
        Window window = glfwGetX11Window(this->pWindow);
        //Atom property
        //Type type;
        //int format;
        //int mode;
        //unsigned char* pData... // NOTE: pData is somehow raw icon data
        //int numElements...
        //XChangeProperty(pDisplay, window, _NET_WM_ICON, type, format, mode, pData, numElements)
    #endif // __linux__
    #ifdef TARGET_OS_MAC || _MACOSX
        // TODO: Implement me
        NSWindow window = glfwGetCocoaWindow();
        //NSImage icon = ??;
    #endif // TARGET_OS_MAC
    // Set Big Application Icon filename
    this->bigApplicationIcon = filename;

    /* TODO: Review this function
        GLFWimage images[2];
        images[0] = load_icon("my_icon.png");
        images[1] = load_icon("my_icon_small.png");
        glfwSetWindowIcon(window, 2, images); */
}

std::string Game::getWindowCaption()
{
    // Return the window Caption
    // NOTE: there is no way to get a window caption / title in glfw :(
    return this->windowCaption;
}

void Game::setWindowCaption(std::string caption)
{
    // Set the window caption
    glfwSetWindowTitle(this->pWindow, caption.c_str());
    // Set the new window caption
    this->windowCaption = caption;
}

bool Game::isWindowMinimized()
{
    // Return if the window is iconified or not
    return glfwGetWindowAttrib(this->pWindow, GLFW_ICONIFIED);
}

void Game::minimiseWindow()
{
    // Minimise the application window
    glfwIconifyWindow(this->pWindow);
}

void Game::restoreWindow()
{
    // Restore the application window
    glfwRestoreWindow(this->pWindow);
}

bool Game::isWindowVisible()
{
   return glfwGetWindowAttrib(this->pWindow, GLFW_VISIBLE);
}

void Game::hideWindow()
{
    glfwHideWindow(this->pWindow);
}

void Game::showWindow()
{
    glfwShowWindow(this->pWindow);
}

bool Game::saveScreenShot()
{
    // Send a message to the console
    std::cout << "bool Game::saveScreenShot()" << std::endl;

    // TODO: Put your screenshot saving code here

    // Send a message to the console
    std::cout << "bool Game::saveScreenShot() success" << std::endl;
    // screenshot saved
    return true;
}

bool Game::saveScreenShot(std::string filename)
{
    // Send a message to the console
    std::cout << "bool Game::saveScreenShot(" << filename << ")" << std::endl;

    // TODO: Put your screenshot saving code here

    // Send a message to the console
    std::cout << "bool Game::saveScreenShot(" << filename << ") success" << std::endl;

    // screenshot saved
    return true;
}

int Game::getWindowX()
{
    int xpos = 0;
    int ypos = 0;
    glfwGetWindowPos(this->pWindow, &xpos, &ypos);
    return xpos;
}

void Game::setWindowX(int windowX)
{
    glfwSetWindowPos(this->pWindow, this->windowX, this->windowY);
}

int Game::getWindowY()
{
    int xpos = 0;
    int ypos = 0;
    glfwGetWindowPos(this->pWindow, &xpos, &ypos);
    return ypos;
}

void Game::setWindowY(int windowY)
{
    glfwSetWindowPos(this->pWindow, this->windowX, this->windowY);
}

void Game::setWindowPosition(int windowX, int windowY)
{
    glfwSetWindowPos(this->pWindow, this->windowX, this->windowY);
}

int Game::getWindowWidth()
{
    int width = 0;
    int height = 0;
    glfwGetWindowSize(this->pWindow, &width, &height);
    return width;
}

int Game::getWindowHeight()
{
    int width = 0;
    int height = 0;
    glfwGetWindowSize(this->pWindow, &width, &height);
    return height;
}

int Game::getWindowFrameWidth()
{
    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(this->pWindow, &width, &height);
    return width;
}

int Game::getWindowFrameHeight()
{
    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(this->pWindow, &width, &height);
    return height;
}

int Game::getResolutionX()
{
    return this->xResolution;
}

int Game::getResolutionY()
{
    return this->yResolution;
}

void Game::setResolution(int xResolution, int yResolution)
{
//////////    //glfwWindowHint(GLFW_DECORATED, GL_TRUE);
//////////    //// Compute the 'Monitor' Parameter for GLFW
//////////    //GLFWmonitor* pGLFWMonitor = ((this->config.getDisplayMode() == EDM_FULLSCREEN) ? glfwGetPrimaryMonitor() : 0);
//////////    //glfwSetWindowMonitor(this->pWindow, pGLFWMonitor, this->windowX, this->windowY, xResolution, yResolution, GLFW_DONT_CARE);
//////////
//////////    GLFWmonitor* pGLFWMonitor = glfwGetWindowMonitor(this->pWindow);
//////////    //glfwSetWindowMonitor(this->pWindow, pGLFWMonitor, this->windowX, this->windowY, xResolution, yResolution, GLFW_DONT_CARE);
//////////    glfwSetWindowMonitor(this->pWindow, pGLFWMonitor, 0.0f, 0.0f, xResolution, yResolution, GLFW_DONT_CARE);
//////////    glfwSetWindowPos(this->pWindow, 0.0f, 0.0f);
////////////////    glfwSetWindowSize(this->pWindow, xResolution, yResolution);
//
//    // Send a Message to the Console
//    std::cout << "void Game::setResolution(int xResolution, int yResolution)" << std::endl;
//    // Retain a local reference to the old window
//    GLFWwindow* pOldWindow = this->pWindow;
//    // Reset Window Hints
//    glfwDefaultWindowHints();
//    // Set Window Hints depending on DisplayMode
//    switch(this->displayMode)
//    {
//        case EDM_FULLSCREEN_WINDOW:
//        {
//            // Make the window have no border and no close button
//            glfwWindowHint(GLFW_DECORATED, GL_FALSE);
//            //glfwWindowHint(GLFW_DECORATED, GL_TRUE);
//            // Make the window the focus of input
//            glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
//            //// Make the window not iconified
//            //glfwWindowHint(GLFW_ICONIFIED, GL_FALSE);
//            // Make the window unresizable
//            glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//            // Make the window Visible
//            glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
//            // Don't Automatically Iconify When Focus is lost
//            glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
//            /* TODO: The code here apparently forces fullscreen window borderless */
//            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
//            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
//            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
//            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
//            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
//            break;
//        }
//        case EDM_FULLSCREEN:
//        {
//            // Make the window have no border and no close button
//            glfwWindowHint(GLFW_DECORATED, GL_FALSE);
//            //glfwWindowHint(GLFW_DECORATED, GL_TRUE);
//            // Make the window the focus of input
//            glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
//            //// Make the window not iconified
//            //glfwWindowHint(GLFW_ICONIFIED, GL_FALSE);
//            // Make the window unresizable
//            glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//            // Make the window Visible
//            glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
//            // Don't Automatically Iconify When Focus is lost
//            glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
//            break;
//        }
//        case EDM_WINDOW:
//        {
//            // Does the window have a border and a close button
//            //glfwWindowHint(GLFW_DECORATED, GL_FALSE);
//            glfwWindowHint(GLFW_DECORATED, GL_TRUE);
//            // Make the window the focus of input
//            glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
//            //// Make the window not iconified
//            //glfwWindowHint(GLFW_ICONIFIED, GL_FALSE);
//            // Make the window unresizable
//            glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//            // Make the window Visible
//            glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
//            // Don't Automatically Iconify When Focus is lost
//            glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
//            break;
//        }
//        default:
//        {
//            break;
//        }
//    }
//    // Compute the 'Monitor' Parameter for GLFW
//    GLFWmonitor* pGLFWMonitor = ((this->config.getDisplayMode() == EDM_FULLSCREEN) ? glfwGetPrimaryMonitor() : 0);
//    // Create the Game Window
//    this->pWindow = glfwCreateWindow(xResolution, yResolution, "", pGLFWMonitor, pOldWindow);
//    // If there was no window made handle that
//    if (this->pWindow == 0)
//    {
//        // Send a message to the console
//        std::cout << "ERROR: Unable to make a new window. Failed to set Resolution to: (" << xResolution << ", " << yResolution << ")" << std::endl;
//        // Restore window pointer
//        this->pWindow = pOldWindow;
//        // Return
//        return;
//    }
////    // Blank out the Context
////    glfwMakeContextCurrent(0);
////
////    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
////        /* Share data from the old rendering context with the new one
////            when data is shared between contexts, data persists until all contexts which share
////            data are also deleted :) Textures belong to rendering contexts so we are really all.
////            Shared information includes, textures, shaders and display lists*/
////        if (pOldWindow != 0)
////            wglShareLists(glfwGetWGLContext(pOldWindow), glfwGetWGLContext(this->pWindow));
//////        bool result = wglCopyContext(glfwGetWGLContext(pOldWindow), glfwGetWGLContext(this->pWindow), GL_ALL_ATTRIB_BITS);
//////        std::cout << "%%% glfwGetWGLContext(pOldWindow): " << glfwGetWGLContext(pOldWindow) << std::endl;
//////        std::cout << "%%% glfwGetWGLContext(this->pWindow): " << glfwGetWGLContext(this->pWindow) << std::endl;
//////        if (result  == false)
//////            exit(0);
////
////    #endif // _WIN32 || _WIN64
////    #ifdef __linux__ || _LINUX
////        // TODO: Implement me
////    #endif // __linux__
////    #ifdef TARGET_OS_MAC || _MACOSX
////        // TODO: Implement me
////    #endif // TARGET_OS_MAC
//    // Make the window context current
//    glfwMakeContextCurrent(this->pWindow);
//
//    // Turn blending on
//    glEnable(GL_BLEND);
//        // Set default blending mode to make alpha transparent channel for all textures
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    // Enable use of 2d textures
//    glEnable(GL_TEXTURE_2D);
//        // Use nearest filter (stops distortion from linear sampling)
//        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//        // Repeat a texture when UV's are out of normalised range
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    //// Enable Depth Test
//    //glEnable(GL_DEPTH_TEST);
//        //// Set the Depth Test Function
//        //glDepthFunc(GL_LEQUAL);
//    //// Enable stencil
//    //glEnable(GL_STENCIL_TEST);
//
//    // Free input system
//    this->inputSystem.free();
//    // Set the window handle for the input system
//    this->inputSystem.setWindow(this->pWindow);
//    // ReInitialise input system
//    this->inputSystem.init();
//    // Set the window caption
//    this->setWindowCaption(this->windowCaption);
//    // Set the application's small icon
//    this->setApplicationIconSmall(this->smallApplicationIcon);
//    // Set the application's big icon
//    this->setApplicationIconBig(this->bigApplicationIcon);
//    // Delete the old window
//    glfwDestroyWindow(pOldWindow);
//    // Set GLFW window callbacks
//    this->setWindowCallBacks();
//    // Setup VSync
//    if (this->vSync == false)
//    {
//        // Turn off Vsync
//        glfwSwapInterval(0);
//    }
//    else
//    {
//        // Turn off Vsync
//        glfwSwapInterval(1);
//    }
////    // ************************
////    // * FORCE WINDOW REFRESH * // NOTE: This was done because win7 didn't automatically adjust for fullscreen mode
////    // ************************
////    /* TODO: Notify postprocessing
////        renderNodes and GBuffer of change in resolution */
////    // Minimise Window
////    this->minimiseWindow();
////    // Restore Window
////    this->restoreWindow();
//    // If there is a GameState fire the onSetResolution callback
//    if (this->pGameState != 0)
//        this->pGameState->onWindowChangeResolution(xResolution, yResolution);
//    // Set xResolution
//    this->xResolution = xResolution;
////    // Update our config
////    this->config.setWidth(this->xResolution);
//    // Set Camera ViewPort Width
//    this->camera2D.setViewPortWidth(this->xResolution);
//    // Set yResolution
//    this->yResolution = yResolution;
//    // Set Camera ViewPort Height
//    this->camera2D.setViewPortHeight(this->yResolution);
////    // Update our config
////    this->config.setHeight(this->yResolution);
}

bool Game::isWindowResizable()
{
    return glfwGetWindowAttrib(this->pWindow, GLFW_RESIZABLE);
}

bool Game::isWindowBordered()
{
    return glfwGetWindowAttrib(this->pWindow, GLFW_DECORATED);
}

void Game::showWindowBorder()
{
    // TODO: Implement me (we need to recreate the window with the correct border hints)
}

void Game::hideWindowBorder()
{
    // TODO: Implement me (we need to recreate the window with the correct border hints)
}

void Game::fullScreenMode()
{
//    // Don't change the DisplayMode unless we have to
//    if (this->displayMode == EDM_FULLSCREEN)
//        return;
//    // Send a message to the console
//    std::cout << "void Game::setFullScreenMode()" << std::endl;
//    // Retain a local reference to the old window
//    GLFWwindow* pOldWindow = this->pWindow;
//    // Compute the 'Monitor' Parameter for GLFW
//    GLFWmonitor* pGLFWMonitor = glfwGetPrimaryMonitor(); // glfwGetPrimaryMonitor causes GLFW to use fullscreen mode
//    // Make the window have no border and no close button
//    glfwWindowHint(GLFW_DECORATED, GL_FALSE);
//    // Make the window the focus of input
//    glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
//    // Make the window unresizable
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//    // Make the window Visible
//    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
//    // Don't Automatically Iconify When Focus is lost
//    glfwWindowHint(GLFW_AUTO_ICONIFY, GL_TRUE);
//    // Create the Game Window
//    this->pWindow = glfwCreateWindow(this->xResolution, this->yResolution, "", pGLFWMonitor, 0);
//    // If there was no window made handle that
//    if (this->pWindow == 0)
//    {
//        // Send a message to the console
//        std::cout << "ERROR: Unable to make a new window. Failed to swap to FullScreenMode" << std::endl;
//        // Restore window pointer
//        this->pWindow = pOldWindow;
//        // Return
//        return;
//    }
//    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
//        /* Share data from the old rendering context with the new one
//            when data is shared between contexts, data persists until all contexts which share
//            data are also deleted :) Textures belong to rendering contexts so we are really all.
//            Shared information includes, textures, shaders and display lists*/
//        if (pOldWindow != 0)
//            wglShareLists(glfwGetWGLContext(pOldWindow), glfwGetWGLContext(this->pWindow));
//    #endif // _WIN32 || _WIN64
//    #ifdef __linux__ || _LINUX
//        // TODO: Determine if context sharing is necessary
//    #endif // __linux__ || _LINUX
//    #ifdef TARGET_OS_MAC || _MACOSX
//        // TODO: Determine if context sharing is necessary
//    #endif // TARGET_OS_MAC || _MACOSX
//    // Make the window context current
//    glfwMakeContextCurrent(this->pWindow);
//    // Set the window handle for the input system
//    this->inputSystem.setWindow(this->pWindow);
//    // ReInitialise input system
//    this->inputSystem.init();
//    // Set the window caption
//    this->setWindowCaption(this->windowCaption);
//    // Set the application's small icon
//    this->setApplicationIconSmall(this->smallApplicationIcon);
//    // Set the application's big icon
//    this->setApplicationIconBig(this->bigApplicationIcon);
//    // If there is an oldWindow (this function might have been called without a window)
//    if (pOldWindow != 0)
//    {
//        // Delete the old window
//        glfwDestroyWindow(pOldWindow);
//    }
//    // Set the Display Mode
//    this->displayMode = EDM_FULLSCREEN;
//    // Set GLFW window callbacks
//    this->setWindowCallBacks();
//    // Set VSync
//    if (this->vSync == false)
//    {
//        // Turn off Vsync
//        glfwSwapInterval(0);
//    }
//    else
//    {
//        // Turn on Vsync
//        glfwSwapInterval(1);
//    }
//    /* TODO: Notify postprocessing
//        renderNodes and GBuffer of change in resolution */
//    // Fire the onFullScreen callback
//    if (this->pGameState != 0)
//        this->pGameState->onWindowFullScreen(true);
}

void Game::fullScreenWindowedMode()
{
//    // Don't change the DisplayMode unless we have to
//    if (this->displayMode == EDM_FULLSCREEN_WINDOW)
//        return;
//    // Send a message to the console
//    std::cout << "void Game::fullScreenWindowedMode()" << std::endl;
//    // Retain a local reference to the old window
//    GLFWwindow* pOldWindow = this->pWindow;
//    // Compute the 'Monitor' Parameter for GLFW
//    GLFWmonitor* pGLFWMonitor = 0; // 0 causes GLFW to use windowed mode
//    // Make the window have no border and no close button
//    glfwWindowHint(GLFW_DECORATED, GL_FALSE);
//    // Make the window the focus of input
//    glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
//    // Make the window unresizable
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//    // Make the window Visible
//    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
//    // Don't Automatically Iconify When Focus is lost
//    glfwWindowHint(GLFW_AUTO_ICONIFY, GL_TRUE);
//    /* TODO: The code here apparently forces fullscreen window borderless */
//    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
//    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
//    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
//    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
//    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
//    // Create the Game Window
//    this->pWindow = glfwCreateWindow(this->xResolution, this->yResolution, "", pGLFWMonitor, 0);
//    // If there was no window made handle that
//    if (this->pWindow == 0)
//    {
//        // Send a message to the console
//        std::cout << "ERROR: Unable to make a new window. Failed to swap to FullScreenWindowedMode" << std::endl;
//        // Restore window pointer
//        this->pWindow = pOldWindow;
//        // Return
//        return;
//    }
//    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
//        /* Share data from the old rendering context with the new one
//            when data is shared between contexts, data persists until all contexts which share
//            data are also deleted :) Textures belong to rendering contexts so we are really all.
//            Shared information includes, textures, shaders and display lists*/
//        if (pOldWindow != 0)
//            wglShareLists(glfwGetWGLContext(pOldWindow), glfwGetWGLContext(this->pWindow));
//    #endif // _WIN32 || _WIN64
//    #ifdef __linux__ || _LINUX
//        // TODO: Determine if context sharing is necessary
//    #endif // __linux__ || _LINUX
//    #ifdef TARGET_OS_MAC || _MACOSX
//        // TODO: Determine if context sharing is necessary
//    #endif // TARGET_OS_MAC || _MACOSX
//    // Make the window context current
//    glfwMakeContextCurrent(this->pWindow);
//    // Set the window handle for the input system
//    this->inputSystem.setWindow(this->pWindow);
//    // ReInitialise input system
//    this->inputSystem.init();
//    // Set the window caption
//    this->setWindowCaption(this->windowCaption);
//    // Set the application's small icon
//    this->setApplicationIconSmall(this->smallApplicationIcon);
//    // Set the application's big icon
//    this->setApplicationIconBig(this->bigApplicationIcon);
//    // If there is an oldWindow (this function might have been called without a window)
//    if (pOldWindow != 0)
//    {
//        // Delete the old window
//        glfwDestroyWindow(pOldWindow);
//    }
//    // Set the Display Mode
//    this->displayMode = EDM_FULLSCREEN_WINDOW;
//    // Set GLFW window callbacks
//    this->setWindowCallBacks();
//    // Set VSync
//    if (this->vSync == false)
//    {
//        // Turn off Vsync
//        glfwSwapInterval(0);
//    }
//    else
//    {
//        // Turn on Vsync
//        glfwSwapInterval(1);
//    }
//    /* TODO: Notify postprocessing
//        renderNodes and GBuffer of change in resolution */
//    // Fire the onFullScreen callback
//    if (this->pGameState != 0)
//        this->pGameState->onWindowFullScreen(true);
}

void Game::windowedMode()
{
//    // Don't change the DisplayMode unless we have to
//    if (this->displayMode == EDM_WINDOW)
//        return;
//    // Send a message to the console
//    std::cout << "void Game::windowedMode()" << std::endl;
//    // Retain a local reference to the old window
//    GLFWwindow* pOldWindow = this->pWindow;
//    // Compute the 'Monitor' Parameter for GLFW
//    GLFWmonitor* pGLFWMonitor = 0; // 0 causes GLFW to use windowed mode
//    // Does the window have a border and a close button
//    glfwWindowHint(GLFW_DECORATED, GL_TRUE);
//    // Make the window the focus of input
//    glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
//    // Make the window unresizable
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//    // Make the window Visible
//    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
//    // Don't Automatically Iconify When Focus is lost
//    glfwWindowHint(GLFW_AUTO_ICONIFY, GL_TRUE);
//    // Create the Game Window
//    this->pWindow = glfwCreateWindow(this->xResolution, this->yResolution, "", pGLFWMonitor, 0);
//    // If there was no window made handle that
//    if (this->pWindow == 0)
//    {
//        // Send a message to the console
//        std::cout << "ERROR: Unable to make a new window. Failed to swap to WindowedMode" << std::endl;
//        // Restore window pointer
//        this->pWindow = pOldWindow;
//        // Return
//        return;
//    }
//    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
//        /* Share data from the old rendering context with the new one
//            when data is shared between contexts, data persists until all contexts which share
//            data are also deleted :) Textures belong to rendering contexts so we are really all.
//            Shared information includes, textures, shaders and display lists*/
//        if (pOldWindow != 0)
//            wglShareLists(glfwGetWGLContext(pOldWindow), glfwGetWGLContext(this->pWindow));
//    #endif // _WIN32 || _WIN64
//    #ifdef __linux__ || _LINUX
//        // TODO: Determine if context sharing is necessary
//    #endif // __linux__ || _LINUX
//    #ifdef TARGET_OS_MAC || _MACOSX
//        // TODO: Determine if context sharing is necessary
//    #endif // TARGET_OS_MAC || _MACOSX
//    // Make the window context current
//    glfwMakeContextCurrent(this->pWindow);
//    // Set the window handle for the input system
//    this->inputSystem.setWindow(this->pWindow);
//    // ReInitialise input system
//    this->inputSystem.init();
//    // Set the window caption
//    this->setWindowCaption(this->windowCaption);
//    // Set the application's small icon
//    this->setApplicationIconSmall(this->smallApplicationIcon);
//    // Set the application's big icon
//    this->setApplicationIconBig(this->bigApplicationIcon);
//    // If there is an oldWindow (this function might have been called without a window)
//    if (pOldWindow != 0)
//    {
//        // Delete the old window
//        glfwDestroyWindow(pOldWindow);
//    }
//    // Set the Display Mode
//    this->displayMode = EDM_WINDOW;
//    // Set GLFW window callbacks
//    this->setWindowCallBacks();
//    // Set VSync
//    if (this->vSync == false)
//    {
//        // Turn off Vsync
//        glfwSwapInterval(0);
//    }
//    else
//    {
//        // Turn on Vsync
//        glfwSwapInterval(1);
//    }
//    /* TODO: Notify postprocessing
//        renderNodes and GBuffer of change in resolution */
//    // Fire the onFullScreen callback
//    if (this->pGameState != 0)
//        this->pGameState->onWindowFullScreen(false);
}

void Game::turnOnVSync()
{
    // Set local VSync flag
    this->vSync = true;
    /* NOTE: This function doesn't seem to work on all graphic cards and operating systems
        it doesn't work on Windows7 for instance i.e. glfwSwapInterval(0); */
    // Turn off Vsync
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        // Turn on vertical screen sync under Windows.
        // (I.e. it uses the WGL_EXT_swap_control extension)
        typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int interval);
        PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");;
        if(wglSwapIntervalEXT)
        {
            wglSwapIntervalEXT(1); // NOTE: 1 Turns it on 0 turns it off
            return;
        }
    #endif // _WIN32 || _WIN64
    #ifdef __linux__ || _LINUX
        // TODO: Yet untested
        // Turn on vertical screen sync under Linux (normal)
        typedef void (*PFNGLXSWAPINTERVALEXTPROC)(Display *dpy, GLXDrawable drawable, int interval);
        PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalEXT");
        if (glXSwapIntervalEXT)
        {
            glXSwapIntervalEXT(1); // NOTE: 1 Turns it on 0 turns it off
            return;
        }
        // Turn on vertical screen sync under Linux (MESA)
        typedef void (*PFNGLXSWAPINTERVALMESAPROC)(Display *dpy, GLXDrawable drawable, int interval);
        PFNGLXSWAPINTERVALMESAPROC glXSwapIntervalEXT = (PFNGLXSWAPINTERVALMESAPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalMESA");
        if (glXSwapIntervalEXT)
        {
            glXSwapIntervalEXT(1); // NOTE: 1 Turns it on 0 turns it off
            return;
        }
        // Turn on vertical screen sync under Linux (SGI)
        typedef void (*PFNGLXSWAPINTERVALSGIPROC)(Display *dpy, GLXDrawable drawable, int interval);
        PFNGLXSWAPINTERVALSGIPROC glXSwapIntervalEXT = (PFNGLXSWAPINTERVALSGIPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalSGI");
        if (glXSwapIntervalEXT)
        {
            glXSwapIntervalEXT(1); // NOTE: 1 Turns it on 0 turns it off
            return;
        }
        return;
    #endif // __linux__
    #ifdef TARGET_OS_MAC || _MACOSX
        // TODO: Implement me
        NSOpenGLCPSwapInterval(); // NOTE: This is for mac 'cocoa'
        kCGLCPSwapInterval(); // NOTE: This is for the CGL api
        return;
    #endif // TARGET_OS_MAC
	// Turn off Vertical Sync
	glfwSwapInterval(0);
	// Return
	return;
}

void Game::turnOffVSync()
{
    // Set local VSync flag
    this->vSync = false;
    /* NOTE: This function doesn't seem to work on all graphic cards and operating systems
        it doesn't work on Windows7 for instance*/
    // TODO: VSync Functions for each operating system
    //// Turn off Vsync
    //glfwSwapInterval(0);
    #ifdef _WIN32 || _WIN64 || _WIN7 || _WINXP
        // Turn on vertical screen sync under Windows.
        // (I.e. it uses the WGL_EXT_swap_control extension)
        typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int interval);
        PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
        wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
        if(wglSwapIntervalEXT)
            wglSwapIntervalEXT(0); // 1 Turns it on 0 turns it off
    #endif // _WIN32 || _WIN64
    #ifdef __linux__ || _LINUX
        // TODO: Yet untested
        // Turn on vertical screen sync under Linux (normal)
        typedef void (*PFNGLXSWAPINTERVALEXTPROC)(Display *dpy, GLXDrawable drawable, int interval);
        PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalEXT");
        if (glXSwapIntervalEXT)
        {
            glXSwapIntervalEXT(0); // NOTE: 1 Turns it on 0 turns it off
            return;
        }
        // Turn on vertical screen sync under Linux (MESA)
        typedef void (*PFNGLXSWAPINTERVALMESAPROC)(Display *dpy, GLXDrawable drawable, int interval);
        PFNGLXSWAPINTERVALMESAPROC glXSwapIntervalEXT = (PFNGLXSWAPINTERVALMESAPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalMESA");
        if (glXSwapIntervalEXT)
        {
            glXSwapIntervalEXT(0); // NOTE: 1 Turns it on 0 turns it off
            return;
        }
        // Turn on vertical screen sync under Linux (SGI)
        typedef void (*PFNGLXSWAPINTERVALSGIPROC)(Display *dpy, GLXDrawable drawable, int interval);
        PFNGLXSWAPINTERVALSGIPROC glXSwapIntervalEXT = (PFNGLXSWAPINTERVALSGIPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalSGI");
        if (glXSwapIntervalEXT)
        {
            glXSwapIntervalEXT(0); // NOTE: 1 Turns it on 0 turns it off
            return;
        }
        return;
    #endif // __linux__
    #ifdef TARGET_OS_MAC || _MACOSX
        // TODO: Implement me
        NSOpenGLCPSwapInterval(); // NOTE: This is for mac 'cocoa'
        kCGLCPSwapInterval(); // NOTE: This is for the CGL api
        return;
    #endif // TARGET_OS_MAC
	// Turn off Vertical Sync
	glfwSwapInterval(0);
	// Return
	return;
}

float* Game::getClearColour()
{
    // Return a pointer to the 4 element array for background colour // NOTE: Alternative glGetFloatv(GL_COLOUR_CLEAR_VALUE, clearColour);
    return this->clearColour;
}

float Game::getClearColourRed()
{
    return this->clearColour[0];
}

float Game::getClearColourGreen()
{
    return this->clearColour[1];
}

float Game::getClearColourBlue()
{
    return this->clearColour[2];
}

float Game::getClearColorAlpha()
{
    return this->clearColour[3];
}

void Game::setClearColour(float red, float green, float blue, float alpha)
{
    // Set the background colour's red, green, blue and alpha component
    this->clearColour[0] = red;
    this->clearColour[1] = green;
    this->clearColour[2] = blue;
    this->clearColour[3] = alpha;
    // Set the Clear colour
    glClearColor(this->clearColour[0], this->clearColour[1], this->clearColour[2], this->clearColour[3]);
}

void Game::setLimitFramesPerSecond(bool state)
{
    //  the present time the frame rate limiter was called
    this->now = 0;
    //  the last time the frame rate limiter was called
    this->then = 0;
    //  the frame accumulator
    this->accumulator = 0;
    // Toggle the frame timer
    if (limitFramesPerSecond != state)
    {
        // If we are turning on the limit  the timer else turn it off
        if (state == true)
        {
            // Stop the timer, ting it
            this->frameTimer.stop();
            // Restart the timer
            this->frameTimer.start();
        }
        else
        {
            // Stop the timer, ting it
            this->frameTimer.stop();
        }
    }
    // Set the toggle for the frame rate limiter
    this->limitFramesPerSecond = state;
}

void Game::createGameStates()
{
    // send a message to the console
    std::cout << "Game::createStates()" << std::endl;

    // A temporary handle to a created game state
    IGameState* pGameState = 0;

    // Message to Console
    std::cout << "    Create State: DEFAULTGAMESTATE" << std::endl;
    // Create a new state instance
    pGameState = new DefaultGameState(this);
    // Register the new state with the gameStateMap
    this->gameStateMap["DEFAULTGAMESTATE"] = pGameState;

    // Message to Console
    std::cout << "    Create State: BATTLEGAMESTATE" << std::endl;
    // Create a new state instance
    pGameState = new BattleGameState(this);
    // Register the new state with the gameStateMap
    this->gameStateMap["BATTLEGAMESTATE"] = pGameState;

    // Message to Console
    std::cout << "    Create State: INTROGAMESTATE" << std::endl;
    // Create a new state instance
    pGameState = new IntroGameState(this);
    // Register the new state with the gameStateMap
    this->gameStateMap["INTROGAMESTATE"] = pGameState;

    // Message to Console
    std::cout << "    Create State: MAINGAMESTATE" << std::endl;
    // Create a new state instance
    pGameState = new MainMenuGameState(this);
    // Register the new state with the gameStateMap
    this->gameStateMap["MAINMENUGAMESTATE"] = pGameState;
}

void Game::changeGameState(const char* state)
{
    // send a message to the console
    std::cout << "Game::changeGameState(" << state << ")" << std::endl;
    // Get the length of the state string
    unsigned int stateNameLength = strlen(state);
    // If the state string is empty then change to an empty state
    if(stateNameLength == 0)
    {
        // If there is already a state assigned
        if (this->pGameState != 0)
        {
            // Call the stop method on the current state
            this->pGameState->stop();
            // Call the exit method on the current state
            this->pGameState->exit();
            // Set the state pointer to null
            this->pGameState = 0;
        }
        // Send a message to the console
        std::cout << "State set to empty" << std::endl;
        // Nothing else to do so return
        return;
    }
    // Find the state on the gameStateMap
    std::map<std::string, IGameState*>::iterator i = this->gameStateMap.find(Utils::toUpper(state));
    // If a state was found with the name registered then change the state
    if(i != this->gameStateMap.end())
    {
        // Get a handle to the state on the map
        IGameState* pGameState = (IGameState*) i->second;
        // If the current state is different from the state chage request then action a state change
        if (this->pGameState != pGameState)
        {
            /* NOTE: I left this note here. It's worthy of consideration for end users
                If we pause the engine then change state, depending on the way you
                want state changes to behave you might want a state to resume before changing
                just in case it was paused.
                //this->resume(); */
            // Call the exit method for the existing state
            if (this->pGameState != 0)
                this->pGameState->exit();
            // Set the current state to the new state
            this->pGameState = pGameState;
            // Flush the Input System
            this->inputSystem.flush();
            // Call the new state's enter method
            this->pGameState->enter();
            // Call the new state's start method
            this->pGameState->start();
            // send a message to the console
            std::cout << "Game::changeGameState(" << state << ")" << "Successful" << std::endl;
            // state change successful
            return;
        }
        // send a message to the console
        std::cout << "Game::changeGameState() state is already: " << state << ". No change made." << std::endl;
        // state change unsuccessful
        return;
    }
    // send a message tot he console
    std::cout << "Game::changeGameState() unable to find " << state << ". " << std::endl;

    // state change unsuccessful
    return;
}

void Game::deleteGameStates()
{
    // Send a message to the console
    std::cout << "void Game::deleteGameStates()" << std::endl;
    // Delete each state registered on the gameStateMap
    for(std::map<std::string, IGameState*>::iterator i = this->gameStateMap.begin(); i != this->gameStateMap.end(); i++)
        delete i->second;
    // Clear the gameStateMap
    this->gameStateMap.clear();
    // Send a message to the console
    std::cout << "void Game::deleteGameStates() success" << std::endl;
}

void Game::start()
{
    // Send a message to the console
    std::cout << "void Game::start()" << std::endl;

    // Only Start if the game isn't already running
    if (this->isRunning() == true)
        return;

    // Create the GameStates
    this->createGameStates();

    // start the application timer
    this->applicationTimer.start();

    // Change Game State
    //this->changeGameState("DEFAULTGAMESTATE");
    //this->changeGameState("INTROGAMESTATE");
    this->changeGameState("MAINMENUGAMESTATE");
    //this->changeGameState("BATTLEGAMESTATE");

    // if framerate limiter is true then start the frame timer
    if (this->limitFramesPerSecond == true)
        this->frameTimer.start();
    // start the frames per second counter
    this->fpsCounter.start();
    // start the renderss per second counter
    this->rpsCounter.start();
    // set the application state to running
    this->running = true;

    // Send a message to the console
    std::cout << "void Game::start() success" << std::endl;
}

void Game::stop()
{
    // ********
    // * STOP *
    // ********

    // Don't stop if we aren't running
    if (this->isRunning() == false)
        return;
    // Send a message to the console
    std::cout << "void Game::stop()" << std::endl;
    // Empty the game state
    this->changeGameState("");
    // Delete all created game states
    this->deleteGameStates();
    // Set running to false
    this->setRunning(false);
    // Stop the game timer
    this->applicationTimer.stop();
    // if frame rate limiter is on then stop the counter
    if (this->limitFramesPerSecond == true)
        this->frameTimer.stop();
    // turn off the frame rate limiter
    this->limitFramesPerSecond = false;
    // Stop keeping track of Frames per second
    this->fpsCounter.stop();
    // Stop keeping track of Renders per second
    this->rpsCounter.stop();
    // Send a message to the console
    std::cout << "void Game::stop() success" << std::endl;
}

void Game::pause()
{
    // *********
    // * PAUSE *
    // *********

    // Send a message to the console
    std::cout << "Game::pause()" << std::endl;
    // Set the paused state to true
    this->paused = true;
    // Pause the application timer
    this->applicationTimer.pause();
}

void Game::resume()
{
    // **********
    // * RESUME *
    // **********

    // Send a message to the console
    std::cout << "Game::resume()" << std::endl;
    // Set the paused state to false
    this->paused = false;
    // Resume the application timer
    this->applicationTimer.resume();
}

void Game::bossSpeak(const char* text)
{
    // Send a message to the console
    std::cout << text << std::endl;

    //void BattleGameState::bossSpeak(const char* text)
    //{
        /*
        SDL_Color debugColour;
        debugColour.r = 255;
        debugColour.g = 255;
        debugColour.b = 255;
        FontUtils::drawString(this->game->pFont, debugColour, text, 0, this->config.getHeight()-45, this->game->pScreen);
        */
    //}
}

void Game::createBossBullet(float x, float y, float xVel, float yVel)
{
    Bullet bullet;
        bullet.setRadius(5.0f);
        bullet.setX(x);
        bullet.setY(y);
        bullet.setXVelocity(xVel);
        bullet.setYVelocity(yVel);
    this->bossBullets.push_back(bullet);
}

void Game::createPlayerBullet(float x, float y, float xVel, float yVel)
{
    Bullet bullet;
        bullet.setRadius(5.0f);
        bullet.setX(x);
        bullet.setY(y);
        bullet.setXVelocity(xVel);
        bullet.setYVelocity(yVel);
    this->playerBullets.push_back(bullet);
}

bool Game::loadPlayer(const char* filename)
{
    this->pPlayerScript = this->makeLuaState();
    if (this->pPlayerScript == 0)
    {
        // send a message to the console
        std::cout << "ERROR: Could not create Lua State for Player." << std::endl;
        // failure
        return false;
    }

    if (luaL_dofile(this->pPlayerScript, filename) != 0)
    {
        // send a message to the console
        std::cout << "ERROR: problem with " << filename << std::endl;
        std::cout << lua_tostring(this->pPlayerScript, -1) << std::endl;
        // failure
        return false;
    }

    luabridge::push(this->pPlayerScript, &(this->player));
    lua_setglobal(this->pPlayerScript, "this");

    // Success
    return true;
}

void Game::thinkPlayer()
{
    this->player.think();

    luabridge::push(this->pPlayerScript, &(this->player) );
    lua_setglobal(this->pPlayerScript, "this");

    lua_getglobal(this->pPlayerScript, "main");
    lua_pcall(this->pPlayerScript, 0, 0, 0);
    // get number of elements on the stack
    int stackElements = lua_gettop(this->pPlayerScript);
    // if thre is an element on the stack there was an error
    if (stackElements != 0)
    {
        // Send a message to the console
        std::cout << "*******************************" << std::endl;
        // Send a message to the console
        std::cout << "ERROR: void Boss::" << std::endl;
        // TODO: Need to be able print the script name here
        // send error message to the console
        std::cout << "ERROR: " << lua_tostring(this->pPlayerScript, -1) << std::endl;
        std::cout << "*******************************" << std::endl;
    }
}

void Game::updatePlayer()
{
    this->player.update();
}

void Game::drawPlayer()
{
    this->player.draw();
}

void Game::clearPlayer()
{
    this->player.clear();
}

void Game::freePlayer()
{
    this->player.free();
}

void Game::updatePlayerBullets()
{
    for (std::vector<Bullet>::iterator iter = this->playerBullets.begin(); iter != this->playerBullets.end(); iter++)
    {
        (*iter).update();
    }
}

void Game::drawPlayerBullet()
{
    for (std::vector<Bullet>::iterator iter = this->playerBullets.begin(); iter != this->playerBullets.end(); iter++)
    {
        this->getOpenGLDraw()->filledCircleRBGA((*iter).getX(), (*iter).getY(), (*iter).getRadius(), 1.0f, 1.0f, 0.0f, 1.0f);
    }
}

void Game::clearPlayerBullets()
{
    this->playerBullets.clear();
}

bool Game::loadBoss(const char* filename)
{
    this->pBossScript = this->makeLuaState();
    if (this->pBossScript == 0)
    {
        // send a message to the console
        std::cout << "ERROR: Could not create Lua State for Boss." << std::endl;
        // failure
        return false;
    }

    if (luaL_dofile(this->pBossScript, filename) != 0)
    {
        // send a message to the console
        std::cout << "ERROR: problem with " << filename << std::endl;
        std::cout << lua_tostring(this->pBossScript, -1) << std::endl;
        // failure
        return false;
    }

    luabridge::push(this->pBossScript, &(this->boss));
    lua_setglobal(this->pBossScript, "this");

    // Success
    return true;
}

void Game::thinkBoss()
{
    this->boss.think();

    luabridge::push(this->pBossScript, &(this->boss) );
    lua_setglobal(this->pBossScript, "this");

    lua_getglobal(this->pBossScript, "main");
    lua_pcall(this->pBossScript, 0, 0, 0);
    // get number of elements on the stack
    int stackElements = lua_gettop(this->pBossScript);
    // if thre is an element on the stack there was an error
    if (stackElements != 0)
    {
        // Send a message to the console
        std::cout << "*******************************" << std::endl;
        // Send a message to the console
        std::cout << "ERROR: void Boss::" << std::endl;
        // TODO: Need to be able print the script name here
        // send error message to the console
        std::cout << "ERROR: " << lua_tostring(this->pBossScript, -1) << std::endl;
        std::cout << "*******************************" << std::endl;
    }
}

void Game::updateBoss()
{
    this->boss.update();
}

void Game::drawBoss()
{
    this->boss.draw();
}

void Game::clearBoss()
{
    this->boss.clear();
}

void Game::freeBoss()
{
    this->boss.free();
}

void Game::updateBossBullets()
{
    for (std::vector<Bullet>::iterator iter = this->bossBullets.begin(); iter != this->bossBullets.end(); iter++)
    {
        (*iter).update();
    }
}

void Game::drawBossBullets()
{
    for (std::vector<Bullet>::iterator iter = this->bossBullets.begin(); iter != this->bossBullets.end(); iter++)
    {
        this->getOpenGLDraw()->filledCircleRBGA((*iter).getX(), (*iter).getY(), (*iter).getRadius(), 1.0f, 1.0f, 0.0f, 1.0f);
    }
}

void Game::clearBossBullets()
{
    this->bossBullets.clear();
}

lua_State* Game::makeLuaState()
{
    // Make a pointer for the New Lua State
    lua_State* pLuaState = 0;
    // Create the new LuaState
    pLuaState = luaL_newstate();
    // Make sure we have a valid luaState
    if (pLuaState == 0)
    {
        // Send a message to the console
        std::cout << "ERROR: Could not create Lua State!" << std::endl;
        return 0;
    }
    // Let this state use default lualibraries
    luaL_openlibs(pLuaState);

    // BIND ENGINE CLASSES
    // Bind String Utils Namespace
    LuaBinding::StringUtilsBind(pLuaState);
    // Bind the GameConfig Class
    LuaBinding::GameConfigBind(pLuaState);
    // Bind the Camera2D Class
    LuaBinding::Camera2DBind(pLuaState);
    // Bind the Camera3D Class
    LuaBinding::Camera3DBind(pLuaState);
    // Bind the Colour Class
    LuaBinding::ColourBind(pLuaState);
    // Bind the OpenGLDraw Class
    LuaBinding::OpenGLDrawBind(pLuaState);
    // Bind the Boss Class
    LuaBinding::BossBind(pLuaState);
    // Bind the Timer Class
    LuaBinding::TimerBind(pLuaState);
    // Bind the Frame Counter Class
    LuaBinding::FrameCounterBind(pLuaState);
    // Bind the FPSLimiter Class
    LuaBinding::FPSLimiterBind(pLuaState);
    // Bind the Physics Namespace
    LuaBinding::PhysicsBind(pLuaState);
    // Bind the Bullet Class
    LuaBinding::BulletBind(pLuaState);
    // Bind the Player Class
    LuaBinding::PlayerBind(pLuaState);
    // Bind the Keyboard Class
    LuaBinding::KeyboardBind(pLuaState);
    // Bind the Mouse Class
    LuaBinding::MouseBind(pLuaState);
    // Bind the Mouse Class
    LuaBinding::GamePadBind(pLuaState);
    // Bind the InputSystem Class
    LuaBinding::InputSystemBind(pLuaState);

    // Bind the Game Class
    LuaBinding::GameBind(pLuaState);

    // BIND GLOBALS
    // Grab a Pointer to the Game Instance
    Game* pGame = Game::getInstance();
    luabridge::push(pLuaState, (Game::getInstance()) );
    lua_setglobal(pLuaState, "pGame");

    // Return our LuaState
    return pLuaState;
}

int Game::luaPanic(lua_State* pLua_State)
{
    // Send a message to the console
    std::cout << "LUA PANIC CALLBACK" << std::endl;
    // get number of elements on the stack
    int stackElements = lua_gettop(pLua_State);
    // if there are elements on the stack there was an error
    if (stackElements != 0)
    {
        // Send a message to the console
        std::cout << "*******************************" << std::endl;
        std::cout << "ERROR: " << lua_tostring(pLua_State, -1) << std::endl;
        std::cout << "*******************************" << std::endl;
    }
    // Return Value // TODO: Review this return value
    return 70773;
}

