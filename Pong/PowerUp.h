#ifndef POWER_UP
#define POWER_UP
#include "GameObject.h"
#include "GameConfig.h"

class Player;


class PowerUp : public GameObject{

public:
    PowerUp(powerUpType powerUpID = TEST_ITEM);
    bool getIsActive();
    bool getIsOnScreen();

    void updateDuration();
    void spawnPowerUp(int);
    void setTexture(SDL_Surface *,SDL_Renderer *);
    void pickedUp();


private:
    int duration;
    bool isActive;
    bool isOnScreen;

    powerUpType itemID;

};




#endif // POWER_UP
