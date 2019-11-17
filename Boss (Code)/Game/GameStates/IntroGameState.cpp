#include "IntroGameState.h"
#include "Game.h"

void IntroGameState::enter()
{
    // *********
    // * ENTER *
    // *********

    // Show the Cursor
    this->pGame->getInputSystem()->getMouse()->setVisibility(true);

    // Set Window Caption
    this->pGame->setWindowCaption("Dodgee Software: Boss Tech Demo 2012");

    /*
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    Mix_PlayMusic(this->game->introMusic, -1);
    */

    this->introSequenceTimer.start();
}

void IntroGameState::handleEvents()
{
    // *****************
    // * HANDLE EVENTS *
    // *****************

}

void IntroGameState::think()
{
    // *********
    // * THINK *
    // *********

    if (this->pGame->getInputSystem()->getKeyboard()->isKeyToggled(GLFW_KEY_ESCAPE))
    {
        this->pGame->setRunning(false);
        return;
    }

    if (this->pGame->getInputSystem()->getKeyboard()->isKeyToggled(GLFW_KEY_SPACE) ||
        this->pGame->getInputSystem()->getMouse()->isLeftButtonToggled() == true)
    {
        this->pGame->changeGameState("MAINMENUGAMESTATE");
        return;
    }

    if (introSequenceTimer.getTicks() > 30000)
    {
        this->pGame->changeGameState("MAINMENUGAMESTATE");
    }
}

void IntroGameState::update()
{
    // **********
    // * UPDATE *
    // **********

}

void IntroGameState::draw()
{
    // ********
    // * DRAW *
    // ********

    /*
    SDL_Color winColour;
    winColour.r = 255;
    winColour.g = 255;
    winColour.b = 255;
    FontUtils::drawString(this->game->pFont, winColour, "IntroGameState", 200, 200, this->game->pScreen);

    char buffer[50];
    snprintf(buffer, 50, "Count Down: %i", 30000 - introSequenceTimer.getTicks());
    FontUtils::drawString(this->game->pFont, winColour, buffer, 200, 200 + 45, this->game->pScreen);
    */

    // Background
    pGame->getOpenGLDraw()->boxRBGA(0, 0, pGame->getConfig()->getWidth(), pGame->getConfig()->getHeight(), (64.0f / 255.0f), (64.0f / 255.0f), (244.0f / 255.0f), 1.0f);
}

void IntroGameState::drawGUI()
{
    // ************
    // * DRAW GUI *
    // ************

}

void IntroGameState::exit()
{
    // ********
    // * EXIT *
    // ********

    // Show the Cursor
    this->pGame->getInputSystem()->getMouse()->setVisibility(false);

    // stop
    this->introSequenceTimer.stop();
}

void IntroGameState::start()
{
    // *********
    // * START *
    // *********

    // start
    this->introSequenceTimer.start();
}

void IntroGameState::stop()
{
    // ********
    // * STOP *
    // ********

    // stop
    this->introSequenceTimer.stop();
}

void IntroGameState::pause()
{
    // *********
    // * PAUSE *
    // *********

    // pause
    this->introSequenceTimer.pause();
}

void IntroGameState::resume()
{
    // **********
    // * RESUME *
    // **********

    // resume
    this->introSequenceTimer.resume();
}
