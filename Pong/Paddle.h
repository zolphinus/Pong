#ifndef PADDLE
#define PADDLE

#include "GameConfig.h"


class Paddle : public GameObject
{
public:
    Paddle();
    ~Paddle();

private:
    bool isAI;

};

#endif // PADDLE
