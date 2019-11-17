
#include "Game.h"

void Game::run(int argc, char *argv[])
{
    if (init() == true)
    {
        while (this->isRunning == true)
        {
            this->handleEvents();
            this->think();
            this->update();
            this->draw();
        }
    }
    this->quit();
}

bool Game::init()
{
    std::cout << "Game::init()" << std::endl;
    if (initWindow() == false) return false;
    if (initAudio() == false) return false;
    if (initText() == false) return false;
    this->isRunning = true;
    this->createWorld();
    return true;
}

bool Game::initWindow()
{
    std::cout << "Game::initWindow()" << std::endl;
    pScreen = SDL_SetVideoMode(640, 480, 32, SDL_DOUBLEBUF | SDL_SWSURFACE);
    SDL_WM_SetCaption( "Moving Platform", NULL );
    SDL_ShowCursor(SDL_TRUE);
    return true;
}

void Game::createWorld()
{
    player.setWidth(20);
    player.setHeight(20);
    player.setX(640/2 - player.getWidth()/2);
    player.setY(480/2 - player.getHeight()/2);

    platform.setWidth(50);
    platform.setHeight(20);
    platform.setX(640/2 - player.getWidth()/2);
    platform.setY(480 - 80);
    platform.setXVelocity(1.0f);

    SDL_Rect ground;
    ground.x = 0;
    ground.y = 480 - 20;
    ground.w = 640;
    ground.h = 480;
    worldRects.push_back(ground);

    SDL_Rect roof;
    roof.x = 0;
    roof.y = 0;
    roof.w = 640;
    roof.h = 20;
    worldRects.push_back(roof);

    SDL_Rect leftWall;
    leftWall.x = 0;
    leftWall.y = 20;
    leftWall.w = 20;
    leftWall.h = 440;
    worldRects.push_back(leftWall);

    SDL_Rect rightWall;
    rightWall.x = 620;
    rightWall.y = 20;
    rightWall.w = 20;
    rightWall.h = 440;
    worldRects.push_back(rightWall);

    gravity = 1.0f;
    playerSpeed = 2.0f;
    player.setFalling(true);
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
    return true;
}

void Game::handleEvents()
{
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
    Uint8* pKeys;
    pKeys = SDL_GetKeyState(NULL);
    if (pKeys[SDLK_ESCAPE])
    {
        this->isRunning = false;
    }
    if (pKeys[SDLK_LEFT])
    {
        player.setXVelocity(-playerSpeed);
    }
    if (pKeys[SDLK_RIGHT])
    {
        player.setXVelocity(playerSpeed);
    }
    if (pKeys[SDLK_UP])
    {
        player.setYVelocity(-playerSpeed);
    }
    if (pKeys[SDLK_DOWN])
    {
        player.setYVelocity(playerSpeed);
    }
    if (pKeys[SDLK_SPACE])
    {

    }
}

void Game::think()
{
}

void Game::update()
{
    this->doPlatforms();
    this->doPlayer();
}

void Game::doPlatforms()
{
    platform.update();

    SDL_Rect platformRect;
    platformRect.x = platform.getX();
    platformRect.y = platform.getY();
    platformRect.w = platform.getWidth();
    platformRect.h = platform.getHeight();

    if (platform.getX() < 0)
    {
        platform.setX(0);
        platform.setXVelocity(-platform.getXVelocity());
    }
    if (platform.getX() > 640 - platform.getWidth())
    {
        platform.setX(640 - platform.getWidth());
        platform.setXVelocity(-platform.getXVelocity());
    }
    if (platform.getY() < 0)
    {
        platform.setY(0);
    }
    if (platform.getY() > 480 - platform.getHeight())
    {
        platform.setY(480 - platform.getHeight());
    }
}

void Game::doPlayer()
{
    player.update();
    if (player.isFalling() == true)
    {
        player.setY(player.getY() + gravity);
    }

    int playerFallBoxOverlappingWorldBoxCounter = 0;
    SDL_Rect fallingBox;
    fallingBox.x = player.getX();
    fallingBox.y = player.getY()+ player.getHeight();
    fallingBox.w = player.getWidth();
    fallingBox.h = player.getYVelocity() + player.getYVelocityFromPlatform() + gravity;
    //rectangleRGBA(pScreen, fallingBox.x, fallingBox.y, fallingBox.x + fallingBox.w, fallingBox.y + fallingBox.h, 255, 0, 0, 255);

    SDL_Rect playerRect;
    playerRect.x = player.getX();
    playerRect.y = player.getY();
    playerRect.w = player.getWidth();
    playerRect.h = player.getHeight();
    rectangleRGBA(pScreen, playerRect.x, playerRect.y, playerRect.x + playerRect.w, playerRect.y + playerRect.h, 255, 0, 0, 255);

    SDL_Rect future;
    future.x = player.getX() + player.getXVelocity() + player.getXVelocityFromPlatform();
    future.y = player.getY() + player.getYVelocity() + player.getYVelocityFromPlatform() + gravity;
    future.w = player.getWidth();
    future.h = player.getHeight();
    rectangleRGBA(pScreen, future.x, future.y, future.x + future.w, future.y + future.h, 255, 0, 0, 255);

// ****

    std::vector<SDL_Rect>::iterator iter;
    for(iter = worldRects.begin(); iter != worldRects.end(); iter++)
    {

        if (player.isFalling() == true)
        {
            if (isCollision(playerRect, (*iter), false) == true)
            {
                player.setFalling(false);
                player.setY((*iter).y - player.getHeight());
            }
        }
        else
        {
            if (isCollision(playerRect, (*iter), false) == true)
            {
                playerFallBoxOverlappingWorldBoxCounter++;
            }
        }
    }
    if (playerFallBoxOverlappingWorldBoxCounter == 0)
        player.setFalling(true);

    if (player.getX() < 0)
    {
        player.setX(0);
    }
    if (player.getX() > 640 - player.getWidth())
    {
        player.setX(640 - player.getWidth());
    }
    if (player.getY() < 0)
    {
        player.setY(0);
    }
    if (player.getY() > 480 - player.getHeight())
    {
        player.setY(480 - player.getHeight());
        player.setFalling(false);
    }
    player.setXVelocity(0.0f);
    player.setYVelocity(0.0f);
}

void Game::draw()
{
    SDL_Rect one;
    one.x = 100;
    one.y = 100;
    one.w = 50;
    one.h = 50;
    rectangleRGBA(pScreen, one.x, one.y, one.x + one.w, one.y + one.h, 160, 160, 255, 255);

    SDL_Rect two;
    two.x = 120;
    two.y = 120;
    two.w = 50;
    two.h = 50;
    rectangleRGBA(pScreen, two.x, two.y, two.x + two.w, two.y + two.h, 160, 160, 255, 255);

    if (isCollision(one, two, false) == true)
    {
        SDL_Rect intersect;
        intersect = overlap(one, two);
        rectangleRGBA(pScreen, intersect.x, intersect.y, intersect.x + intersect.w, intersect.y + intersect.h, 255, 0, 0, 255);
        std::cout << "intersectX: " << intersect.x << std::endl;
        std::cout << "intersectY: " << intersect.y << std::endl;
        std::cout << "intersectW: " << intersect.w << std::endl;
        std::cout << "intersectH: " << intersect.h << std::endl;
    }

    std::vector<SDL_Rect>::iterator iter;
    for(iter = worldRects.begin(); iter != worldRects.end(); iter++)
    {
        rectangleRGBA(pScreen, iter->x, iter->y, iter->x + iter->w, iter->y + iter->h, 160, 160, 255, 255);
    }

    // Draw Platform
    boxRGBA(pScreen, platform.getX(), platform.getY(), platform.getX() + platform.getWidth(), platform.getY() + platform.getHeight(), 160, 160, 255, 255);
    // Draw Player
    boxRGBA(pScreen, player.getX(), player.getY(), player.getX() + player.getWidth(), player.getY() + player.getHeight(), 160, 160, 255, 255);
    SDL_Flip(pScreen);
    boxRGBA(pScreen, 0, 0, 640, 480, 64, 64, 224, 255);
}

void Game::quit()
{
    std::cout << "Game::quit()" << std::endl;
}

Game* Game::pInstance = NULL;

Game* Game::getInstance()
{
    if (pInstance != NULL) return pInstance;
    pInstance = new Game();
    return pInstance;
}

bool Game::isCollision( SDL_Rect one, SDL_Rect two, bool eighty )
{
 double left1, left2;
    double right1, right2;
    double top1, top2;
    double bottom1, bottom2;
    if ( eighty == true )
    {
        left1 = one.x + one.w*.1;
        left2 = two.x + two.w*.1;
        right1 = one.x + one.w*.9;
        right2 = two.x + two.w*.9;
        top1 = one.y + one.h*.1;
        top2 = two.y + two.h*.1;
        bottom1 = one.y + one.h*.9;
        bottom2 = two.y + two.h*.9;
    }
    else
    {
        left1 = one.x;
        left2 = two.x;
        right1 = one.x + one.w;
        right2 = two.x + two.w;
        top1 = one.y;
        top2 = two.y;
        bottom1 = one.y + one.h;
        bottom2 = two.y + two.h;
    }

    // test to see if any side of one is inside two
    if ( bottom1 < top2 )
        return false;
    if ( top1 > bottom2 )
        return false;
    if ( right1 < left2 )
        return false;
    if ( left1 > right2 )
        return false;
    return true;
}

SDL_Rect Game::overlap(SDL_Rect one, SDL_Rect two)
{
    SDL_Rect overlap;
    overlap.x = 0;
    overlap.y = 0;
    overlap.w = 0;
    overlap.h = 0;
    float dx = 0.0f;
    float dy = 0.0f;
    if(two.x >= one.x)
    {
        dx = (one.x + one.w) - two.x;
        overlap.x = two.x;
        overlap.w = dx;
    }
    if(two.x < one.x)
    {
        dx = (two.x + two.w) - one.x;
        overlap.x = one.x;
        overlap.w = dx;
    }
    if(two.y >= one.y)
    {
        dy = (one.y + one.h) - two.y;
        overlap.y = two.y;
        overlap.h = dy;

    }
    if(two.y < one.y)
    {
        dy = (two.y + two.h) - one.y;
        overlap.y = one.y;
        overlap.h = dy;
    }
    return overlap;

}
