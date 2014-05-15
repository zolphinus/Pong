#include "PowerUp.h"
#include "GameConfig.h"

PowerUp::PowerUp(powerUpType powerUpID){

    if(powerUpID > TOTAL_POWER_UPS)
    {
        itemID = powerUpID;
    }
    else
    {
        itemID = TEST_ITEM;
    }

    isActive = false;
    isOnScreen = false;
    duration = 0;
}

bool PowerUp::getIsActive(){
    return isActive;
}

bool PowerUp::getIsOnScreen(){
    return isOnScreen;
}

void PowerUp::pickedUp(){
    isActive = true;
    isOnScreen = false;
}


void PowerUp::updateDuration(){
    if(duration > 0 )
    {
        duration--;
    }
    else
    {
        isActive = false;
    }
}


void PowerUp::spawnPowerUp(int newDuration){
    int randY = rand() % SCREEN_HEIGHT - GameObject::gameObjectRect.h;
    int centerX = SCREEN_WIDTH/2 - GameObject::gameObjectRect.w/2;

    GameObject::gameObjectRect.y = randY;
    GameObject::gameObjectRect.x = centerX;

    duration = newDuration;
    isOnScreen = true;
    isActive = false;
}

void PowerUp::setTexture(SDL_Surface *newSurface,SDL_Renderer *renderer)
{
    if(gameObjectTexture != NULL)
    {
        SDL_DestroyTexture(gameObjectTexture);
    }
    gameObjectTexture = SDL_CreateTextureFromSurface(renderer,newSurface);
    gameObjectRect.w = 96;
    gameObjectRect.h = 96;
}
