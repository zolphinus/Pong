#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "GameConfig.h"
#include "GameObject.h"


class Ball : public GameObject
{
public:
    Ball();
    ~Ball();
    float getXVelocity();
    float getYVelocity();
    void setXVelocity(int newValue);
    void setYVelocity(int newValue);
    void verticleBounce();
    void horizontalBounce();
    float
    XPosition,
    YPosition,
    xVelocity,
    yVelocity;
    double
    movementAngle;

private:
    int
    XVelocity,
    YVelocity;
};

#endif // BALL_H_INCLUDED
