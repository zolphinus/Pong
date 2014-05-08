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


private:
    int duration;
    bool isActive;
    bool isOnScreen;

    void pickedUp();

};

#endif // POWER_UP
