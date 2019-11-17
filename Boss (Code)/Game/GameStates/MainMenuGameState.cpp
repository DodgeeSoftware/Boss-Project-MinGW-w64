#include "MainMenuGameState.h"
#include "Game.h"

void MainMenuGameState::enter()
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
    Mix_PlayMusic(this->game->menuMusic, -1);
    */

    this->mainMenuSequenceTimer.start();
}

void MainMenuGameState::handleEvents()
{
    // *****************
    // * HANDLE EVENTS *
    // *****************

}

void MainMenuGameState::think()
{
    // *********
    // * THINK *
    // *********

    if (this->pGame->getInputSystem()->getKeyboard()->isKeyToggled(GLFW_KEY_ESCAPE))
    {
        this->pGame->setRunning(false);
        return;
    }

//    if (this->pGame->getInputSystem()->getKeyboard()->isKeyToggled(GLFW_KEY_SPACE) ||
//        this->pGame->getInputSystem()->getMouse()->isLeftButtonToggled() == true)
//    {
//        this->pGame->changeGameState("BATTLEGAMESTATE");
//        return;
//    }

    if (this->pGame->getInputSystem()->getKeyboard()->isAnyKey() == true ||
        this->pGame->getInputSystem()->getMouse()->isAnyButton() == true)
    {
        this->pGame->changeGameState("BATTLEGAMESTATE");
        return;
    }

//    if (this->mainMenuSequenceTimer.getTicks() > 30000)
//    {
//        this->pGame->changeGameState("INTROGAMESTATE");
//        return;
//    }
}

void MainMenuGameState::update()
{
    // **********
    // * UPDATE *
    // **********

}

void MainMenuGameState::draw()
{
    // ********
    // * DRAW *
    // ********

    /*
    SDL_Color winColour;
    winColour.r = 255;
    winColour.g = 255;
    winColour.b = 255;
    FontUtils::drawString(this->game->pFont, winColour, "MainMenuGameState", 200, 200 + 45 * 0, this->game->pScreen);
    FontUtils::drawString(this->game->pFont, winColour, "New", 200, 200 + 45 * 1, this->game->pScreen);
    FontUtils::drawString(this->game->pFont, winColour, "Load Game", 200, 200 + 45 * 2, this->game->pScreen);
    FontUtils::drawString(this->game->pFont, winColour, "Options", 200, 200 + 45 * 3, this->game->pScreen);
    FontUtils::drawString(this->game->pFont, winColour, "Credits", 200, 200 + 45 * 4, this->game->pScreen);
    FontUtils::drawString(this->game->pFont, winColour, "Exit", 200, 200 + 45 * 5, this->game->pScreen);

    char buffer[50];
    snprintf(buffer, 50, "Count Down: %i", 30000 - mainMenuSequenceTimer.getTicks());
    FontUtils::drawString(this->game->pFont, winColour, buffer, 200, 200 - 45*2, this->game->pScreen);
    */

    // Background
    pGame->getOpenGLDraw()->boxRBGA(0, 0, pGame->getConfig()->getWidth(), pGame->getConfig()->getHeight(), (64.0f / 255.0f), (64.0f / 255.0f), (244.0f / 255.0f), 1.0f);
}

void MainMenuGameState::drawGUI()
{
    // ************
    // * DRAW GUI *
    // ************

}

void MainMenuGameState::exit()
{
    // ********
    // * EXIT *
    // ********

    // Show the Cursor
    this->pGame->getInputSystem()->getMouse()->setVisibility(false);
    // stop
    this->mainMenuSequenceTimer.stop();
}

void MainMenuGameState::start()
{
    // *********
    // * START *
    // *********

    // start
    this->mainMenuSequenceTimer.start();
}

void MainMenuGameState::stop()
{
    // ********
    // * STOP *
    // ********

    // stop
    this->mainMenuSequenceTimer.stop();
}

void MainMenuGameState::pause()
{
    // *********
    // * PAUSE *
    // *********

    // pause
    this->mainMenuSequenceTimer.pause();
}

void MainMenuGameState::resume()
{
    // **********
    // * RESUME *
    // **********

    // resume
    this->mainMenuSequenceTimer.resume();
}

