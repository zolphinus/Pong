#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "GameConfig.h"
#include "GameObject.h"


class Ball : public GameObject
{
public:
    Ball();
    ~Ball();
    int getXVelocity();
    int getYVelocity();
    int getXPosition();
    int getYPosition();
    void setXVelocity(int newValue);
    void setYVelocity(int newValue);
    void setXPosition(int newValue);
    void setYPosition(int newValue);
    void bounce();


private:
    int
    XVelocity,
    YVelocity,
    XPosition,
    YPosition;
};

#endif // BALL_H_INCLUDED
