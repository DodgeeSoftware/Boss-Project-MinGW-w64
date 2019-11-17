#include "DefaultGameState.h"
#include "Game.h"

void DefaultGameState::enter()
{
    // *********
    // * ENTER *
    // *********

    // Show the Cursor
    this->pGame->getInputSystem()->getMouse()->setVisibility(true);

    // Set Window Caption
    this->pGame->setWindowCaption("Dodgee Software: Boss Tech Demo 2012");

    this->pGame->changeGameState("MAINMENUGAMESTATE");
}

void DefaultGameState::handleEvents()
{
    // *****************
    // * HANDLE EVENTS *
    // *****************

    if (this->pGame->getInputSystem()->getKeyboard()->isKeyToggled(GLFW_KEY_ESCAPE))
    {
        this->pGame->setRunning(false);
        return;
    }
}

void DefaultGameState::think()
{
    // *********
    // * THINK *
    // *********


}

void DefaultGameState::update()
{
    // **********
    // * UPDATE *
    // **********

}

void DefaultGameState::draw()
{
    // ********
    // * DRAW *
    // ********

    /*
    SDL_Color winColour;
    winColour.r = 255;
    winColour.g = 255;
    winColour.b = 255;
    FontUtils::drawString(this->game->pFont, winColour, "DefaultGameState", 200, 200, this->game->pScreen);
    SDL_Flip(game->pScreen);
    boxRGBA(this->game->pScreen, 0, 0, this->config.getWidth(), this->config.getHeight(), 64, 64, 224, 255);
    SDL_Flip(game->pScreen);
    boxRGBA(this->game->pScreen, 0, 0, this->config.getWidth(), this->config.getHeight(), 64, 64, 224, 255);
    */
}

void DefaultGameState::drawGUI()
{
    // ************
    // * DRAW GUI *
    // ************

}

void DefaultGameState::exit()
{
    // ********
    // * EXIT *
    // ********

}

void DefaultGameState::start()
{
    // *********
    // * START *
    // *********

}

void DefaultGameState::stop()
{
    // ********
    // * STOP *
    // ********

}

void DefaultGameState::pause()
{
    // *********
    // * PAUSE *
    // *********

}

void DefaultGameState::resume()
{
    // **********
    // * RESUME *
    // **********

}
