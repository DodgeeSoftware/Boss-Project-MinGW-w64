#include "Game.h"

Game* Game::pInstance = NULL;

Game* Game::getInstance()
{
    if (pInstance != NULL) return pInstance;
    pInstance = new Game();
    return pInstance;
}

int Game::run(int argc, char *argv[])
{
    if (init() == true)
    {
        this->changeState(pDefaultGameState);
        while (this->isRunning == true)
        {
            this->collectInput();
            this->think();
            this->update();
            this->draw();
        }
    }
    this->quit();
    return EXIT_SUCCESS;
}

bool Game::init()
{
    std::cout << "Game::init()" << std::endl;
    if (initWindow() == false) return false;
    if (initAudio() == false) return false;
    if (initText() == false) return false;
    this->isRunning = true;
    this->start();
    return true;
}

bool Game::initWindow()
{
    std::cout << "Game::initWindow()" << std::endl;
    pScreen = SDL_SetVideoMode(640, 480, 32, SDL_DOUBLEBUF | SDL_SWSURFACE);
    SDL_WM_SetCaption( "Boss Tech Demo 2012", NULL );
    SDL_ShowCursor(SDL_FALSE);
    return true;
}

bool Game::initAudio()
{
    std::cout << "Game::initAudio()" << std::endl;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        std::cout << "Could load background." << std::endl;
        std::cout << "Mix_Open Audio: " << Mix_GetError() << std::endl;
        return false;
    }
    playerShootSound = Mix_LoadWAV("media/playerShoot.wav");
    if (playerShootSound == NULL)
    {
        std::cout << "Could load media/playerShoot.wav" << std::endl;
        return false;
    }
    bossHitSound = Mix_LoadWAV("media/bossHitSound.wav");
    if (bossHitSound == NULL)
    {
        std::cout << "Could load media/bossHitSound.wav" << std::endl;
        return false;
    }
    bossExplodeSound = Mix_LoadWAV("media/bossExplode.wav");
    if (bossExplodeSound == NULL)
    {
        std::cout << "Could load media/bossExplode.wav" << std::endl;
        return false;
    }
    gameMusic = Mix_LoadMUS("media/sonic2_boss.ogg");
    if (gameMusic == NULL)
    {
        std::cout << "Could load media/media/0-kru.xm" << std::endl;
        return false;
    }
    victoryMusic = Mix_LoadMUS("media/Victory_Fanfare.ogg");
    if (gameMusic == NULL)
    {
        std::cout << "Could load media/media/Victory_Fanfare.ogg" << std::endl;
        return false;
    }

    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    Mix_PlayMusic(gameMusic, -1);

    return true;
}

bool Game::initText()
{
    std::cout << "Game::initText()" << std::endl;
    if (TTF_Init()==-1)
    {
        std::cout << "TTF_Init: " << (TTF_GetError()) << std::endl;
        return false;
    }
    pFont = TTF_OpenFont("media/arial.ttf", 32);
    if (pFont == NULL )
    {
        std::cout << "Could not open font." << std::endl;
    }
    return true;
}

void Game::start()
{
    player.setRadius(20);
    player.setX(140);
    player.setY(480/2);
    playerSpeed = 2.0f;
    player.setHealth(100);
    player.setMaxHealth(100);

    boss.setRadius(50);
    boss.setX(500);
    boss.setY(480/2);
    boss.setMaxHealth(300);
    boss.setHealth(300);
    boss.setUnderAttack(false);
    pBossScript = luaL_newstate();
    if (pBossScript == NULL)
    {
        std::cout << "Could not create Lua State for Boss." << std::endl;
    }
    else
    {
        luaL_openlibs(pBossScript);
        luabind::open(pBossScript);
        // Tool Chain Lua State
        Boss::bind(pBossScript);
        Timer::bindToLua(pBossScript);
        Game::bindToLua(pBossScript);
        luaL_dofile(pBossScript, "media/BossScript.lua");
        luabind::globals(pBossScript)["Game"] = Game::getInstance();
        luabind::globals(pBossScript)["this"] = &boss;
    }

}

void Game::collectInput()
{
    // Get Operating System Messages
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            this->isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                default:
                    break;
            }
            break;
        default:
            break;
    };

    // Get Keyboard State
    pKeys = SDL_GetKeyState(NULL);

    mouse.update();
}

void Game::think()
{
    if (gameState != NULL) this->gameState->think();

    if (pKeys[SDLK_ESCAPE])
    {
        this->isRunning = false;
    }
    if (player.getHealth() > 0)
    {
        this->doPlayer();
        this->doPlayerBullets();
    }

    if (boss.isDead() == false)
    {
        lua_getglobal(pBossScript, "main");
        lua_call(pBossScript, 0, 0);
        this->doBoss();
        this->doBossBullets();
        if (boss.getHealth() <= 0 && boss.isDead() == false)
        {
            boss.setDead(true);
            Mix_PlayMusic(victoryMusic, 0);
            explodeEffectTimer.start();
            youWinTimer.start();
            boss.setXVelocity(0.0f);
            boss.setYVelocity(0.0f);

        }
    }
    if (youWinTimer.getTicks() > 30000)
    {
        this->isRunning = false;
    }
}

void Game::update()
{

    boss.update();
    for (std::vector<Bullet>::iterator iter = bossBullets.begin(); iter != bossBullets.end(); iter++)
    {
        (*iter).update();
    }
    player.update();
    for (std::vector<Bullet>::iterator iter = playerBullets.begin(); iter != playerBullets.end(); iter++)
    {
        (*iter).update();
    }

}

void Game::doPlayer()
{
    // Reset Player speed
    player.setXVelocity(0.0f);
    player.setYVelocity(0.0f);
    // Make the player move based on input
    if (pKeys[SDLK_w])
    {
        player.setYVelocity(-playerSpeed);
    }
    if (pKeys[SDLK_a])
    {
        player.setXVelocity(-playerSpeed);
    }
    if (pKeys[SDLK_s])
    {
        player.setYVelocity(playerSpeed);
    }
    if (pKeys[SDLK_d])
    {
        player.setXVelocity(playerSpeed);
    }
    // Keep player restricted to Screen Bounds
    if (player.getX() - player.getRadius() < 0)
    {
        player.setX(0 + player.getRadius());
    }
    if (player.getX() > 640 - player.getRadius())
    {
        player.setX(640 - player.getRadius());
    }
    if (player.getY() - player.getRadius() < 45)
    {
        player.setY(45 + player.getRadius());
    }
    if (player.getY() > 440 - player.getRadius())
    {
        player.setY(440 - player.getRadius());
    }
    // Make the player shoot
    if (mouse.isLeftClick() == true)
    {
        float dx = (mouse.getX() - player.getX());
        float dy = (mouse.getY() - player.getY());
        float dm = sqrt(dx * dx + dy * dy);
        if (fabs(dm) < 1) dm = 1;
        dx = (dx / dm);
        dy = (dy / dm);
        Bullet bullet;
        bullet.setRadius(5.0f);
        bullet.setX(player.getX() + dx * (player.getRadius() + bullet.getRadius()));
        bullet.setY(player.getY() + dy * (player.getRadius() + bullet.getRadius()));
        bullet.setXVelocity(dx*5);
        bullet.setYVelocity(dy*5);
        playerBullets.push_back(bullet);
        Mix_PlayChannel(-1, playerShootSound, 0);
    }

}

void Game::doPlayerBullets()
{
    SDL_Circle bossCircle;
    bossCircle.x = boss.getX();
    bossCircle.y = boss.getY();
    bossCircle.radius = boss.getRadius();
    int numberOfBulletsHittingBoss = 0;
    for (std::vector<Bullet>::iterator iter = playerBullets.begin(); iter != playerBullets.end(); iter++)
    {
        SDL_Circle bullet;
        bullet.x = (*iter).getX();
        bullet.y = (*iter).getY();
        bullet.radius = (*iter).getRadius();
        if (Physics::isCollision(bossCircle, bullet))
        {
            playerBullets.erase(iter);
            iter--;
            if (boss.isImmuneToDamage() == false)
            {
                boss.setUnderAttack(true);
                underAttackTimer.start();
                numberOfBulletsHittingBoss++;
                boss.setHealth(boss.getHealth() - 1);
                Mix_PlayChannel(-1, bossHitSound, 0);
            }
            continue;
        }

        if ((*iter).getX() + (*iter).getRadius() < 0)
        {
            playerBullets.erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getX() - (*iter).getRadius() > 640)
        {
            playerBullets.erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getY() + (*iter).getRadius() < 55)
        {
            playerBullets.erase(iter);
            iter--;
            continue;
        }
        if ((*iter).getY() - (*iter).getRadius() > 425)
        {
            playerBullets.erase(iter);
            iter--;
            continue;
        }
    }
    if (numberOfBulletsHittingBoss == 0 && boss.isUnderAttack() == true)
    {
        boss.setUnderAttack(false);
    }
}

void Game::doBoss()
{
    // Draw the Boss bar
    boxRGBA(pScreen, 640/2-100, 10, 640/2+100,30, 255, 0, 0, 255 ); // draw boss bar background
    unsigned int modifier = ((float)boss.getHealth()/ (float)boss.getMaxHealth()) * 200.0f; // Calculate health space
    boxRGBA(pScreen, 640/2-100, 10, 640/2-100 + modifier,30, 255, 255, 0, 255 ); // draw boss bar
}

void Game::doBossBullets()
{
    for (std::vector<Bullet>::iterator iter = bossBullets.begin(); iter != bossBullets.end(); iter++)
    {
        if ((*iter).getX() + (*iter).getRadius() < 0)
        {
            bossBullets.erase(iter);
            iter--;
        }
        if ((*iter).getX() - (*iter).getRadius() > 640)
        {
            bossBullets.erase(iter);
            iter--;
        }
        if ((*iter).getY() + (*iter).getRadius() < 0)
        {
            bossBullets.erase(iter);
            iter--;
        }
        if ((*iter).getY() - (*iter).getRadius() > 480)
        {
            bossBullets.erase(iter);
            iter--;
        }
    }
}

void Game::draw()
{
    //    SDL_Color debugColour;
    //    debugColour.r = 255;
    //    debugColour.g = 255;
    //    debugColour.b = 255;
    //    char buffer[50];
    //    sprintf(buffer, "You win timer: %i", youWinTimer.getTicks());
    //    FontUtils::drawString(pFont, debugColour, buffer, 0, 200, pScreen);
    if (boss.isDead() == false)
    {
        if (underAttackTimer.getTicks() > 0)
        {
            filledCircleRGBA(pScreen, boss.getX(), boss.getY(), boss.getRadius(), 160, 160, 255, 255);
            circleRGBA(pScreen, boss.getX(), boss.getY(), boss.getRadius(), 255, 255, 255, 255);
            if (underAttackTimer.getTicks()> 100)
                underAttackTimer.stop();
        }
        else
        {
            filledCircleRGBA(pScreen, boss.getX(), boss.getY(), boss.getRadius(), 160, 160, 255, 255);
        }
    }
    else
    {
        SDL_Color winColour;
        winColour.r = 255;
        winColour.g = 255;
        winColour.b = 255;

        FontUtils::drawString(pFont, winColour, "YOU WIN!!!", 260, 240-22, pScreen);
        filledCircleRGBA(pScreen, boss.getX(), boss.getY(), boss.getRadius(), 0, 0, 0, 255);

        srand (time(NULL));
        if (explodeEffectTimer.getTicks() > 500)
        {
            Mix_PlayChannel(-1, bossExplodeSound, 0);
            explodeEffectTimer.stop();
            explodeEffectTimer.start();

        }
        for(int i = 0; i < 100; i++)
        {
            float dx = ((float)(rand() / (float)RAND_MAX) -((float)rand() / (float)RAND_MAX));
            float dy = ((float)(rand() / (float)RAND_MAX) -((float)rand() / (float)RAND_MAX));

            filledCircleRGBA(pScreen, boss.getX()+dx*boss.getRadius(), boss.getY()+dy*boss.getRadius(), 5, 255, 255, 0, 255);
        }
    }

    if (mouse.getButton1() == true)
    {
        // Draw Player
        filledCircleRGBA(pScreen, player.getX(), player.getY(), player.getRadius(), 160, 160, 255, 255);
        circleRGBA(pScreen, player.getX(), player.getY(), player.getRadius(), 255, 255, 255, 255);
    }
    else
    {
        // Draw Player
        filledCircleRGBA(pScreen, player.getX(), player.getY(), player.getRadius(), 160, 160, 255, 255);
    }

    // Draw Players Gun
    float dx = (mouse.getX() - player.getX());
    float dy = (mouse.getY() - player.getY());
    float dm = sqrt(dx * dx + dy * dy);
    if (fabs(dm) < 1) dm = 1;
    dx = (dx / dm) * player.getRadius();
    dy = (dy / dm) * player.getRadius();
    lineRGBA(pScreen, player.getX(), player.getY(), player.getX() + dx, player.getY() + dy, 0, 0, 0, 255);
    filledCircleRGBA(pScreen, player.getX() + dx, player.getY() + dy, 2, 0, 0,0, 255);

    for (std::vector<Bullet>::iterator iter = playerBullets.begin(); iter != playerBullets.end(); iter++)
    {
        filledCircleRGBA(pScreen, (*iter).getX(), (*iter).getY(), (*iter).getRadius(), 255, 255, 0, 255);
    }

    SDL_Circle bossCircle;
    bossCircle.x = boss.getX();
    bossCircle.y = boss.getY();
    bossCircle.radius = boss.getRadius();

    SDL_Circle mouseCircle;
    mouseCircle.x = mouse.getX();
    mouseCircle.y = mouse.getY();
    mouseCircle.radius = 20;

    if (Physics::isCollision(bossCircle, mouseCircle) && boss.isDead() == false)
    {
        circleRGBA(pScreen, mouse.getX(), mouse.getY(), 2, 255, 0, 0, 255);
        boxRGBA(pScreen, mouse.getX()-1, mouse.getY() - 10, mouse.getX()+1, mouse.getY() - 20, 255, 0, 0, 255);
        boxRGBA(pScreen, mouse.getX()-1, mouse.getY() + 10, mouse.getX()+1, mouse.getY() + 20, 255, 0, 0, 255);
        boxRGBA(pScreen, mouse.getX()-10, mouse.getY()-1, mouse.getX()-20, mouse.getY() + 1, 255, 0, 0, 255);
        boxRGBA(pScreen, mouse.getX()+10, mouse.getY()-1, mouse.getX()+20, mouse.getY() + 1, 255, 0, 0, 255);
    }
    else
    {
        circleRGBA(pScreen, mouse.getX(), mouse.getY(), 2, 0, 255, 0, 255);
        boxRGBA(pScreen, mouse.getX()-1, mouse.getY() - 10, mouse.getX()+1, mouse.getY() - 20, 0, 255, 0, 255);
        boxRGBA(pScreen, mouse.getX()-1, mouse.getY() + 10, mouse.getX()+1, mouse.getY() + 20, 0, 255, 0, 255);
        boxRGBA(pScreen, mouse.getX()-10, mouse.getY()-1, mouse.getX()-20, mouse.getY() + 1, 0, 255, 0, 255);
        boxRGBA(pScreen, mouse.getX()+10, mouse.getY()-1, mouse.getX()+20, mouse.getY() + 1, 0, 255, 0, 255);
    }

    SDL_Flip(pScreen);
    boxRGBA(pScreen, 0, 0, 640, 480, 64, 64, 224, 255);
    boxRGBA(pScreen, 0, 440, 640, 480, 0, 0, 0, 255);
    boxRGBA(pScreen, 0, 0, 640, 45, 0, 0, 0, 255);

}

void Game::quit()
{
    std::cout << "Game::quit()" << std::endl;
}

void Game::changeState(IState* gameState)
{
    if (this->gameState != gameState && this->gameState != NULL)
    {
        this->gameState->onExit();
        this->gameState = gameState;
        this->gameState->onEnter();
    }
}

void Game::bindToLua(lua_State* luaState)
{
    luabind::module(luaState)
    [
        luabind::class_<Game>("Game")
        .def("bossSpeak", (void(Game::*)(const char*))& Game::bossSpeak)
    ];
}

void Game::bossSpeak(const char* text)
{
    SDL_Color debugColour;
    debugColour.r = 255;
    debugColour.g = 255;
    debugColour.b = 255;
    FontUtils::drawString(pFont, debugColour, text, 0, 480-45, pScreen);
}
