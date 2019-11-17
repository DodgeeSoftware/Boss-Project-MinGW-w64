#include "BattleGameState.h"
#include "BattleGameState.h"
#include "Game.h"

BattleGameState::BattleGameState(Game* pGame) : IGameState(pGame)
{

}

BattleGameState::~BattleGameState()
{

}

BattleGameState::BattleGameState(const BattleGameState& other) : IGameState(pGame)
{
    // PROTECTED COPY CONSTRUCTOR
}

void BattleGameState::enter()
{
    // *********
    // * ENTER *
    // *********

    // Init Scene
    if (this->initScene() == false)
        return;
    // Init GUI
    if (this->initGUI() == false)
        return;
}

bool BattleGameState::initWindow()
{
    // ***************
    // * INIT WINDOW *
    // ***************

    // Set Window Caption
    this->pGame->setWindowCaption("Dodgee Software: Boss Tech Demo 2012");

    // Success
    return true;
}

bool BattleGameState::initScene()
{
    // **************
    // * INIT SCENE *
    // **************

    // Load Boss
    if (pGame->loadBoss("media/bossScript.lua") == false)
        return false;
    // Load Player
    if (pGame->loadPlayer("media/playerScript.lua") == false)
        return false;

    // Success
    return true;
}

bool BattleGameState::initGUI()
{
    // ************
    // * INIT GUI *
    // ************

    // Show the Cursor
    pGame->getInputSystem()->getMouse()->setVisibility(true);

    // Success
    return true;
}

void BattleGameState::handleEvents()
{
    // *****************
    // * HANDLE EVENTS *
    // *****************

    if (pGame->getInputSystem()->getKeyboard()->isKeyToggled(GLFW_KEY_ESCAPE))
    {
        // Stop the game at the end of this frame
        pGame->setRunning(false);
        return;
    }

    if (pGame->getInputSystem()->getKeyboard()->isKeyToggled(GLFW_KEY_F4))
    {
        // restart the boss fight demo
        this->restart();
    }
}

void BattleGameState::think()
{
    // *********
    // * THINK *
    // *********

    // Think Boss
    pGame->thinkBoss();
    // Think Player
    pGame->thinkPlayer();

    // While the Player still has health
    if (pGame->getPlayer()->getHealth() > 0 &&
        pGame->getPlayer()->isDead() == false)
    {
        // Bound the player to the world boundaries
        this->boundPlayerToWorldBoundaries();
        // Process Player Bullets
        this->doPlayerBulletAndBossBulletCollisions();
        // Do player  bullet collisions with the boss
        this->doPlayerBossCollisions();
    }

    // While the boss is still alive
    if (pGame->getBoss()->getHealth() > 0 &&
        pGame->getBoss()->isDead() == false)
    {
        // Bound the Boss to the world boundaires
        this->boundBossToWorldBoundaries();
        // Bound the boss to the world boundaries
        this->boundBossBulletsToWorldBoundaries();
        // Do boss bullet collisions with the player
        this->doBossBulletAndPlayerBulletCollisions();
    }

    /* After boss is defeated wait a certain
        amount of time before going back to default
        game state */
    if (this->youWinTimer.getTicks() > 5000)
    {
        this->youWinTimer.stop();
        pGame->changeGameState("MAINMENUGAMESTATE");
        return;
    }

    /* After player is dead wait a certain amount of
        time before going back to default game state */
    if (this->youLoseTimer.getTicks() > 5000)
    {
        this->youLoseTimer.stop();
        pGame->changeGameState("MAINMENUGAMESTATE");
        return;
    }

    // Reset boss is under attack timer
    if (this->underAttackTimer.getTicks() > 100)
        this->underAttackTimer.stop();
}

void BattleGameState::update()
{
    // **********
    // * UPDATE *
    // **********

    // update boss
    pGame->updateBoss();
    // update boss bullets
    pGame->updateBossBullets();
    // update player
    pGame->updatePlayer();
    // update player bullets
    pGame->updatePlayerBullets();
}

void BattleGameState::draw()
{
    // ********
    // * DRAW *
    // ********

    /* Draw background */
    pGame->getOpenGLDraw()->boxRBGA(0, 0, pGame->getConfig()->getWidth(), pGame->getConfig()->getHeight(), (64.0f / 255.0f), (64.0f / 255.0f), (244.0f / 255.0f), 1.0f);

    // Draw Boss
    pGame->drawBoss();
    /* Draw different boss gfx when the boss is alive */
    if (pGame->getBoss()->isDead() == false)
    {
        // While boss has recently been hit by a bullet
        if (this->underAttackTimer.getTicks() > 0)
        {
            // Draw the boss with a helo around him
            pGame->getOpenGLDraw()->filledCircleRBGA(pGame->getBoss()->getX(), pGame->getBoss()->getY(), pGame->getBoss()->getRadius(), 160.0f / 255.0f, 160 / 255.0f, 1.0f, 1.0f);
            pGame->getOpenGLDraw()->circleRBGA(pGame->getBoss()->getX(), pGame->getBoss()->getY(), pGame->getBoss()->getRadius(), 1.0f, 1.0f, 1.0f, 1.0f);
        }
        else
        {
            // Draw normal boss circle
            pGame->getOpenGLDraw()->filledCircleRBGA(pGame->getBoss()->getX(), pGame->getBoss()->getY(), pGame->getBoss()->getRadius(), 160.0f / 255.0f, 160.0f / 255.0f, 1.0f, 1.0f);
        }
    }
    else
    {
        // DRAW EXPLODING BOSS
        /*SDL_Color winColour;
        winColour.r = 255;
        winColour.g = 255;
        winColour.b = 255;
        FontUtils::drawString(this->game->pFont, winColour, "YOU WIN!!!", 260, 240-22, this->game->pScreen);
        filledCircleRGBA(this->game->pScreen, this->game->boss.getX(), this->game->boss.getY(), this->game->boss.getRadius(), 0, 0, 0, 255);
        */
        if (explodeEffectTimer.getTicks() > 500)
        {
            //Mix_PlayChannel(-1, this->game->bossExplodeSound, 0);
            this->explodeEffectTimer.stop();
            this->explodeEffectTimer.start();
        }
        for(int i = 0; i < 100; i++)
        {
            float dx = ((float)(rand() / (float)RAND_MAX) -((float)rand() / (float)RAND_MAX));
            float dy = ((float)(rand() / (float)RAND_MAX) -((float)rand() / (float)RAND_MAX));
            pGame->getOpenGLDraw()->filledCircleRBGA(pGame->getBoss()->getX()+dx*pGame->getBoss()->getRadius(), pGame->getBoss()->getY()+dy*pGame->getBoss()->getRadius(), 5.0f, 1.0f, 1.0f, 0.0f, 1.0f);
        }
    }

    // Draw Player
    pGame->drawPlayer();
    /* Draw different player gfx when the player is alive */
    if (pGame->getPlayer()->isDead() == false)
    {
        /* When the user clicks to shoot draw a white outline
            around the player otherwise draw normal player */
        if (pGame->getInputSystem()->getMouse()->isLeftMouseButtonPressed() == true)
        {
            pGame->getOpenGLDraw()->filledCircleRBGA(pGame->getPlayer()->getX(), pGame->getPlayer()->getY(), pGame->getPlayer()->getRadius(), 160.0f / 255.0f, 160.0f / 255.0f, 1.0f, 1.0f);
            pGame->getOpenGLDraw()->circleRBGA(pGame->getPlayer()->getX(), pGame->getPlayer()->getY(), pGame->getPlayer()->getRadius(), 1.0f, 1.0f, 1.0f, 1.0f);
        }
        else
        {
            pGame->getOpenGLDraw()->filledCircleRBGA(pGame->getPlayer()->getX(), pGame->getPlayer()->getY(), pGame->getPlayer()->getRadius(), 160.0f / 255.0f, 160.0f / 255.0f, 1.0f, 1.0f);
        }
        /* Draw Players Gun */
        float dx = (pGame->getInputSystem()->getMouse()->getX() - pGame->getPlayer()->getX());
        float dy = (pGame->getInputSystem()->getMouse()->getY() - pGame->getPlayer()->getY());
        float dm = sqrt(dx * dx + dy * dy);
        if (fabs(dm) < 1) dm = 1;
        dx = (dx / dm) * pGame->getPlayer()->getRadius();
        dy = (dy / dm) * pGame->getPlayer()->getRadius();
        pGame->getOpenGLDraw()->lineRBGA(pGame->getPlayer()->getX(), pGame->getPlayer()->getY(), pGame->getPlayer()->getX() + dx, pGame->getPlayer()->getY() + dy, 0.0f, 0.0f, 0.0f, 1.0f);
        pGame->getOpenGLDraw()->filledCircleRBGA(pGame->getPlayer()->getX() + dx, pGame->getPlayer()->getY() + dy, 2.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    }
    else
    {
        // DRAW EXPLODING PLAYER
        /*SDL_Color winColour;
        winColour.r = 255;
        winColour.g = 255;
        winColour.b = 255;
        FontUtils::drawString(this->game->pFont, winColour, "YOU LOSE!!!", 260, 240-22, this->pame->pScreen);
        filledCircleRGBA(this->game->pScreen, this->game->boss.getX(), this->game->boss.getY(), this->game->boss.getRadius(), 0, 0, 0, 255);
        */
        if (explodeEffectTimer.getTicks() > 500)
        {
            //Mix_PlayChannel(-1, this->game->bossExplodeSound, 0);
            this->explodeEffectTimer.stop();
            this->explodeEffectTimer.start();
        }
        for(int i = 0; i < 100; i++)
        {
            float dx = ((float)(rand() / (float)RAND_MAX) -((float)rand() / (float)RAND_MAX));
            float dy = ((float)(rand() / (float)RAND_MAX) -((float)rand() / (float)RAND_MAX));
            pGame->getOpenGLDraw()->filledCircleRBGA(pGame->getPlayer()->getX()+dx*pGame->getPlayer()->getRadius(), pGame->getPlayer()->getY()+dy*pGame->getPlayer()->getRadius(), 5.0f, 1.0f, 1.0f, 0.0f, 1.0f);
        }
    }

    /* Draw the Player Bullets */
    pGame->drawPlayerBullet();

    /* Draw the boss Bullets */
    pGame->drawBossBullets();

    /* Draw the Cross Hair */
    float oneX = pGame->getBoss()->getX();
    float oneY = pGame->getBoss()->getY();
    float oneRadius = pGame->getBoss()->getRadius();
    float twoX = pGame->getInputSystem()->getMouse()->getX();
    float twoY = pGame->getInputSystem()->getMouse()->getY();
    float twoRadius = 20;
    if (Physics::isCollision(oneX, oneY, oneRadius, twoX, twoY, twoRadius) && pGame->getBoss()->isDead() == false)
    {
        pGame->getOpenGLDraw()->circleRBGA(pGame->getInputSystem()->getMouse()->getX(), pGame->getInputSystem()->getMouse()->getY(), 2.0f, 1.0f, 0.0f, 0.0f, 1.0f);
        pGame->getOpenGLDraw()->boxRBGA(pGame->getInputSystem()->getMouse()->getX() - 1.0f, pGame->getInputSystem()->getMouse()->getY() - 10.0f, pGame->getInputSystem()->getMouse()->getX() + 1.0f, pGame->getInputSystem()->getMouse()->getY() - 20.0f, 1.0f, 0.0f, 0.0f, 1.0f);
        pGame->getOpenGLDraw()->boxRBGA(pGame->getInputSystem()->getMouse()->getX() - 1.0f, pGame->getInputSystem()->getMouse()->getY() + 10.0f, pGame->getInputSystem()->getMouse()->getX() + 1.0f, pGame->getInputSystem()->getMouse()->getY() + 20.0f, 1.0f, 0.0f, 0.0f, 1.0f);
        pGame->getOpenGLDraw()->boxRBGA(pGame->getInputSystem()->getMouse()->getX() - 10.0f, pGame->getInputSystem()->getMouse()->getY() - 1.0f, pGame->getInputSystem()->getMouse()->getX() - 20.0f, pGame->getInputSystem()->getMouse()->getY() + 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
        pGame->getOpenGLDraw()->boxRBGA(pGame->getInputSystem()->getMouse()->getX() + 10.0f, pGame->getInputSystem()->getMouse()->getY() - 1.0f, pGame->getInputSystem()->getMouse()->getX() + 20.0f, pGame->getInputSystem()->getMouse()->getY() + 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    }
    else
    {
        pGame->getOpenGLDraw()->circleRBGA(pGame->getInputSystem()->getMouse()->getX(), pGame->getInputSystem()->getMouse()->getY(), 2.0f, 0.0f, 1.0f, 0.0f, 1.0f);
        pGame->getOpenGLDraw()->boxRBGA(pGame->getInputSystem()->getMouse()->getX() - 1.0f, pGame->getInputSystem()->getMouse()->getY() - 10.0f, pGame->getInputSystem()->getMouse()->getX() + 1.0f, pGame->getInputSystem()->getMouse()->getY() - 20.0f, 0.0f, 1.0f, 0.0f, 1.0f);
        pGame->getOpenGLDraw()->boxRBGA(pGame->getInputSystem()->getMouse()->getX() - 1.0f, pGame->getInputSystem()->getMouse()->getY() + 10.0f, pGame->getInputSystem()->getMouse()->getX() + 1.0f, pGame->getInputSystem()->getMouse()->getY() + 20.0f, 0.0f, 1.0f, 0.0f, 1.0f);
        pGame->getOpenGLDraw()->boxRBGA(pGame->getInputSystem()->getMouse()->getX() - 10.0f, pGame->getInputSystem()->getMouse()->getY() - 1.0f, pGame->getInputSystem()->getMouse()->getX() - 20.0f, pGame->getInputSystem()->getMouse()->getY() + 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
        pGame->getOpenGLDraw()->boxRBGA(pGame->getInputSystem()->getMouse()->getX() + 10.0f, pGame->getInputSystem()->getMouse()->getY() - 1.0f, pGame->getInputSystem()->getMouse()->getX() + 20.0f, pGame->getInputSystem()->getMouse()->getY() + 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    }
}

void BattleGameState::drawGUI()
{
    // ************
    // * DRAW GUI *
    // ************

    // Draw black boxes at top and bottom of screen
    pGame->getOpenGLDraw()->boxRBGA(0, 0, pGame->getConfig()->getWidth(), 45, 0.0f, 0.0f, 0.0f, 1.0f);
    pGame->getOpenGLDraw()->boxRBGA(0, pGame->getConfig()->getHeight() - 40.0f, pGame->getConfig()->getWidth(), pGame->getConfig()->getHeight(), 0.0f, 0.0f, 0.0f, 1.0f);

    // Draw the Boss health bar
    pGame->getOpenGLDraw()->boxRBGA(pGame->getConfig()->getWidth() / 2.0f - 100.0f, 10.0f, pGame->getConfig()->getWidth() / 2.0f + 100.0f, 30.0f, 1.0f, 0.0f, 0.0f, 1.0f); // draw boss bar background
    if (pGame->getBoss()->getHealth() > 0.0f)
    {
        unsigned int modifier = ((float)pGame->getBoss()->getHealth()/ (float)pGame->getBoss()->getMaxHealth()) * 200.0f; // Calculate health space
        pGame->getOpenGLDraw()->boxRBGA(pGame->getConfig()->getWidth() / 2.0f - 100.0f, 10.0f, pGame->getConfig()->getWidth() / 2.0f - 100.0f + modifier,30.0f, 1.0f, 1.0f, 0.0f, 1.0f ); // draw boss bar
    }

    // Draw the Player health bar
    pGame->getOpenGLDraw()->boxRBGA(pGame->getConfig()->getWidth() / 2.0f - 100.0f, pGame->getConfig()->getHeight() - 10.0f, pGame->getConfig()->getWidth() / 2.0f + 100.0f, pGame->getConfig()->getHeight() - 30.0f, 1.0f, 0.0f, 0.0f, 1.0f); // draw boss bar background
    if (pGame->getPlayer()->getHealth() > 0.0f)
    {
        unsigned int modifier = ((float)pGame->getPlayer()->getHealth()/ (float)pGame->getPlayer()->getMaxHealth()) * 200.0f; // Calculate health space
        pGame->getOpenGLDraw()->boxRBGA(pGame->getConfig()->getWidth() / 2.0f - 100.0f, pGame->getConfig()->getHeight() - 10.0f, pGame->getConfig()->getWidth() / 2.0f - 100.0f + modifier, pGame->getConfig()->getHeight() - 30.0f, 1.0f, 1.0f, 0.0f, 1.0f ); // draw boss bar
    }
}

void BattleGameState::exit()
{
    // ********
    // * EXIT *
    // ********

    // Show the Cursor
    pGame->getInputSystem()->getMouse()->setVisibility(false);

    // Clear Boss
    pGame->clearBoss();
    // Free Boss
    pGame->freeBoss();
    // Clear Player
    pGame->clearPlayer();
    // Free Player
    pGame->freePlayer();
}

void BattleGameState::start()
{
    // *********
    // * START *
    // *********

    // restart
    this->restart();

    // stateTimer
    this->stateTimer.start();
}

void BattleGameState::stop()
{
    // ********
    // * STOP *
    // ********

    // stop
    this->underAttackTimer.stop();
    // stop
    this->explodeEffectTimer.stop();
    // stop
    this->youWinTimer.stop();
    // stop
    this->youLoseTimer.stop();

    // stateTimer
    this->stateTimer.stop();
}

void BattleGameState::pause()
{
    // *********
    // * PAUSE *
    // *********

    // pause
    this->underAttackTimer.pause();
    // pause
    this->explodeEffectTimer.pause();
    // pause
    this->youWinTimer.pause();
    // pause
    this->youLoseTimer.pause();

    // stateTimer
    this->stateTimer.pause();
}

void BattleGameState::resume()
{
    // *********
    // * PAUSE *
    // *********

    // resume
    this->underAttackTimer.resume();
    // resume
    this->explodeEffectTimer.resume();
    // resume
    this->youWinTimer.resume();
    // resume
    this->youLoseTimer.resume();

    // stateTimer
    this->stateTimer.resume();
}

void BattleGameState::restart()
{
    //Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    //Mix_PlayMusic(this->game->battleMusic, -1);

    pGame->getPlayer()->setRadius(20);
    pGame->getPlayer()->setX(140);
    pGame->getPlayer()->setY(pGame->getConfig()->getHeight() / 2.0f);
    pGame->getPlayer()->setSpeed(4.0f);
    pGame->getPlayer()->setHealth(100);
    pGame->getPlayer()->setMaxHealth(100);
    pGame->getPlayer()->setUnderAttack(false);
    pGame->getPlayer()->setDead(false);
    pGame->getPlayer()->setState("");
    pGame->getPlayer()->setImmuneToDamage(false);

    pGame->getBoss()->setRadius(50);
    pGame->getBoss()->setX(500);
    pGame->getBoss()->setY(pGame->getConfig()->getHeight() / 2.0f);
    pGame->getBoss()->setMaxHealth(300);
    pGame->getBoss()->setHealth(300);
    pGame->getBoss()->setUnderAttack(false);
    pGame->getBoss()->setState("");
    pGame->getBoss()->setDead(false);
    pGame->getBoss()->setImmuneToDamage(false);

    this->youLoseTimer.stop();
    this->youWinTimer.stop();
    this->explodeEffectTimer.stop();

    pGame->clearBossBullets();

    pGame->clearPlayerBullets();
}

void BattleGameState::doPlayerBulletAndBossBulletCollisions()
{
    // Don't do colisions if the boss is dead
    if (pGame->getBoss()->isDead() == true)
        return;
    // Do Collisions for the players bullts and the boss
    float oneX = pGame->getBoss()->getX();
    float oneY = pGame->getBoss()->getY();
    float oneRadius = pGame->getBoss()->getRadius();
    int numberOfBulletsHittingBoss = 0;
    for (std::vector<Bullet>::iterator iter = pGame->getPlayerBullets()->begin(); iter != pGame->getPlayerBullets()->end(); iter++)
    {
        float twoX = (*iter).getX();
        float twoY = (*iter).getY();
        float twoRadius = (*iter).getRadius();
        if (Physics::isCollision(oneX, oneY, oneRadius, twoX, twoY, twoRadius))
        {
            pGame->playerBullets.erase(iter);
            iter--;
            if (pGame->getBoss()->isImmuneToDamage() == false)
            {
                pGame->getBoss()->setUnderAttack(true);
                underAttackTimer.start();
                numberOfBulletsHittingBoss++;
                pGame->getBoss()->setHealth(pGame->getBoss()->getHealth() - 20);
                //Mix_PlayChannel(-1, pGame->bossHitSound, 0);
                if (pGame->getBoss()->getHealth() <= 0)
                {
                    // Kill Boss
                    this->killBoss();
                }
            }
            continue;
        }

        if ((*iter).getX() + (*iter).getRadius() < 0)
        {
            pGame->playerBullets.erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getX() - (*iter).getRadius() > pGame->getConfig()->getWidth())
        {
            pGame->playerBullets.erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getY() + (*iter).getRadius() < 0)
        {
            pGame->playerBullets.erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getY() - (*iter).getRadius() > pGame->getConfig()->getHeight())
        {
            pGame->playerBullets.erase(iter);
            iter--;
            continue;
        }
    }
    if (numberOfBulletsHittingBoss == 0 && pGame->getBoss()->isUnderAttack() == true)
    {
        pGame->getBoss()->setUnderAttack(false);
    }
}

void BattleGameState::doBossBulletAndPlayerBulletCollisions()
{
    // Don't do collisions if the player is dead
    if (pGame->getPlayer()->isDead() == true)
        return;
    // Do Collisions for the boss's bullts and the player
    float oneX = pGame->getPlayer()->getX();
    float oneY = pGame->getPlayer()->getY();
    float oneRadius = pGame->getPlayer()->getRadius();
    int numberOfBulletsHittingPlayer = 0;
    for (std::vector<Bullet>::iterator iter = pGame->getBossBullets()->begin(); iter != pGame->getBossBullets()->end(); iter++)
    {
        float twoX = (*iter).getX();
        float twoY = (*iter).getY();
        float twoRadius = (*iter).getRadius();

        if (Physics::isCollision(oneX, oneY, oneRadius, twoX, twoY, twoRadius))
        {
            pGame->getBossBullets()->erase(iter);
            iter--;
            if (pGame->getPlayer()->isImmuneToDamage() == false)
            {
                numberOfBulletsHittingPlayer++;
                pGame->getPlayer()->setUnderAttack(true);
                pGame->getPlayer()->setHealth(pGame->getPlayer()->getHealth() - 20);
                //Mix_PlayChannel(-1, pGame->bossHitSound, 0);
                if (pGame->getPlayer()->getHealth() <= 0)
                {
                    this->killPlayer();
                }
            }
            continue;
            if ((*iter).getX() + (*iter).getRadius() < 0)
            {
                pGame->getBossBullets()->erase(iter);
                iter--;
                continue;
            }
            if ((*iter).getX() - (*iter).getRadius() > pGame->getConfig()->getWidth())
            {
                pGame->getBossBullets()->erase(iter);
                iter--;
                continue;
            }
            if ((*iter).getY() + (*iter).getRadius() < 0)
            {
                pGame->getBossBullets()->erase(iter);
                iter--;
                continue;
            }
            if ((*iter).getY() - (*iter).getRadius() > pGame->getConfig()->getHeight())
            {
                pGame->getBossBullets()->erase(iter);
                iter--;
                continue;
            }
        }
        if (numberOfBulletsHittingPlayer == 0 && pGame->getPlayer()->isUnderAttack() == true)
        {
            pGame->getPlayer()->setUnderAttack(false);
        }
    }
}

void BattleGameState::doPlayerBossCollisions()
{
    // Do Collisions for the player and the boss
    float oneX = pGame->getPlayer()->getX();
    float oneY = pGame->getPlayer()->getY();
    float oneRadius = pGame->getPlayer()->getRadius();

    float twoX = pGame->getBoss()->getX();
    float twoY = pGame->getBoss()->getY();
    float twoRadius = pGame->getBoss()->getRadius();

    // Test the player and boss circles
    if (Physics::isCollision(oneX, oneY, oneRadius, twoX, twoY, twoRadius))
    {
        this->killPlayer();
    }
}

void BattleGameState::boundBossToWorldBoundaries()
{
    // TODO: Implement me
}

void BattleGameState::boundPlayerToWorldBoundaries()
{
    // Keep player restricted to Screen Bounds
    if (pGame->getPlayer()->getX() - pGame->getPlayer()->getRadius() < 0)
    {
        pGame->getPlayer()->setX(0 + pGame->getPlayer()->getRadius());
        pGame->getPlayer()->setXVelocity(0.0f);
    }
    if (pGame->getPlayer()->getX() > pGame->getConfig()->getWidth() - pGame->getPlayer()->getRadius())
    {
        pGame->getPlayer()->setX(pGame->getConfig()->getWidth() - pGame->getPlayer()->getRadius());
        pGame->getPlayer()->setXVelocity(0.0f);
    }
    if (pGame->getPlayer()->getY() - pGame->getPlayer()->getRadius() < 45)
    {
        pGame->getPlayer()->setY(45 + pGame->getPlayer()->getRadius());
        pGame->getPlayer()->setYVelocity(0.0f);
    }
    if (pGame->getPlayer()->getY() > pGame->getConfig()->getHeight() - 40.0f - pGame->getPlayer()->getRadius())
    {
        pGame->getPlayer()->setY(pGame->getConfig()->getHeight() - 40.0f - pGame->getPlayer()->getRadius());
        pGame->getPlayer()->setYVelocity(0.0f);
    }
}

void BattleGameState::boundBossBulletsToWorldBoundaries()
{
    // Bound bullets to the screen
    for (std::vector<Bullet>::iterator iter = pGame->getBossBullets()->begin(); iter != pGame->getBossBullets()->end(); iter++)
    {
        if ((*iter).getX() + (*iter).getRadius() < 0)
        {
            pGame->getBossBullets()->erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getX() - (*iter).getRadius() > pGame->getConfig()->getWidth())
        {
            pGame->getBossBullets()->erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getY() + (*iter).getRadius() < 0)
        {
            pGame->getBossBullets()->erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getY() - (*iter).getRadius() > pGame->getConfig()->getHeight())
        {
            pGame->getBossBullets()->erase(iter);
            iter--;
            continue;
        }
    }
}

void BattleGameState::killBoss()
{
    // If boss is already dead then return
    if (pGame->getBoss()->isDead() == true)
        return;
    std::cout << "Boss dies" << std::endl;
    // Set boss's health to 0
    pGame->getBoss()->setHealth(0);
    // Set the boss's dead flag
    pGame->getBoss()->setDead(true);
    // TODO: Play sound effect for death
    //// Play victory music
    //Mix_PlayMusic(this->game->victoryMusic, 0);
    // Start explode timer
    this->explodeEffectTimer.start();
    // Start you win timer
    this->youWinTimer.start();
    // Stop the boss moving
    pGame->getBoss()->setXVelocity(0.0f);
    pGame->getBoss()->setYVelocity(0.0f);
    pGame->getBoss()->setUnderAttack(false);
}

void BattleGameState::killPlayer()
{
    // If player is already dead then return
    if (pGame->getPlayer()->isDead() == true)
        return;
    std::cout << "Player dies" << std::endl;
    // Set player's health to 0
    pGame->getPlayer()->setHealth(0);
    // Set the player's dead flag
    pGame->getPlayer()->setDead(true);
    // TODO: Play sound effect for death
    // Start you lose timer
    this->youLoseTimer.start();
    // Stop the player moving
    pGame->getPlayer()->setXVelocity(0.0f);
    pGame->getPlayer()->setYVelocity(0.0f);
    pGame->getPlayer()->setUnderAttack(false);
}
