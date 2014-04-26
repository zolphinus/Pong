#ifndef PLAYER
#define PLAYER
#include <SDL.h>
#include "GameConfig.h"


class Player : public GameObject
{
public:
    Player();
    ~Player();
    void setAI(AI);

private:
    bool isAI;

};

#endif // Player
