#ifndef POWER_UP
#define POWER_UP
#include "GameObject.h"

class PowerUp : public GameObject{

public:
    PowerUp();
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

};




#endif // POWER_UP
