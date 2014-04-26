#ifndef PADDLE
#define PADDLE

#include "GameConfig.h"
#include "GameObject.h"


class Paddle : public GameObject
{
public:
    Paddle();
    ~Paddle();

private:
    bool isAI;

};

#endif // PADDLE
