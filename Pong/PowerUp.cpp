#include "PowerUp.h"
#include "GameConfig.h"

PowerUp::PowerUp(){
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

void PowerUp::setDuration(int newDuration){
    duration = newDuration;
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
    int centerX = SCREEN_WIDTH - GameObject::gameObjectRect.w;

    GameObject::gameObjectRect.y = randY;
    GameObject::gameObjectRect.x = centerX;

    setDuration(newDuration);
    duration = newDuration;
    isActive = true;
    isOnScreen = false;
}

