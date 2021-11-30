#include "ResourceManager.h"
#include <SDL.h>
#include "SDL_image.h"
#include <iostream>

ResourceManager* ResourceManager::pInstance = NULL;

ResourceManager* ResourceManager::getInstance()
{
    if (pInstance == NULL)
    {
        pInstance = new ResourceManager();
    }
    return pInstance;
}

ResourceManager::ResourceManager()
{
}

Sint32 ResourceManager::addGraphic(SDL_Renderer* gRenderer, const char* file)
{
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);

    if ((initted & flags) != flags) {
        std::cout << "Error init SDL_Image" << IMG_GetError();
    }

    SDL_Texture* Image;
    Image = IMG_LoadTexture(gRenderer, file);

    if (Image == NULL)
    {
        return -1;
    }
    else
    {
        mGraphicsVector.push_back(Image);
        mIDMap.insert(std::pair <std::string, int>(file, mGraphicsVector.size() - 1));
    }
    return mIDMap.find(file)->second;
}

Sint32 ResourceManager::loadAndGetGraphicID(SDL_Renderer* gRenderer, const char* file)
{
    std::map<std::string, int>::iterator it;
    it = mIDMap.find(file);
    if (it != mIDMap.end())
    {
        return mIDMap.find(file)->second;
    }
    else
    {
        return addGraphic(gRenderer, file);
    }
}

SDL_Texture* ResourceManager::getGraphicByID(Sint32 ID)
{
    return mGraphicsVector.at(ID);
}

