#include "GameConfig.h"

GameConfig::GameConfig()
{
    this->width = 640.0f;
    this->height = 480.0f;
}

GameConfig::~GameConfig()
{
    //dtor
}

bool GameConfig::load(std::string filename)
{
    // ********
    // * LOAD *
    // ********

    // Open File
    std::ifstream configFile;
    configFile.open(filename.c_str());
    if (configFile.is_open() == false)
    {
        std::cout << "ERROR: Unable to load file: " << filename.c_str() << std::endl;
        // Faulure
        return false;
    }
    std::string line;
    // Read Width
    std::getline(configFile, line);
    this->width = std::stoi(line);
    // Read Height
    std::getline(configFile, line);
    this->height = std::stoi(line);
    // Close file
    configFile.close();

    // Success
    return true;
}

bool GameConfig::save(std::string filename)
{
    // *******
    //* SAVE *
    // *******

    // Save file
    std::ofstream configFile;
    configFile.open(filename.c_str());

    if (configFile.is_open() == false)
    {
        std::cout << "ERROR: Unable to save file: " << filename.c_str() << std::endl;
        // Faulure
        return false;
    }
    // Write Width
    configFile << this->width << std::endl;
    // Write Height
    configFile << this->height << std::endl;
    // Close File
    configFile.close();

    // Success
    return true;
}

void GameConfig::clear()
{
    // *********
    // * CLEAR *
    // *********

    this->width = 640.0f;
    this->height = 480.0f;
}

void GameConfig::toConsole()
{
    // **************
    // * TO CONSOLE *
    // **************

    std::cout << "GAMECONFIG" << std::endl;
    std::cout << "width: " << this->width << std::endl;
    std::cout << "height: " << this->height << std::endl;
}
