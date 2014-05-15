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
    float getVelocity();
    void setXVelocity(int newValue);
    void setYVelocity(int newValue);
    void verticalBounce();
    void horizontalBounce();
    float xPosition, yPosition;
    double movementAngle;

    void resetBall();

private:
    float
    velocity,
    xVelocity,
    yVelocity;

    void calcVelocities();
};

#endif // BALL_H_INCLUDED
