#include "Ball.h"

Ball::Ball()
{
    do
    {
       movementAngle = rand()%360+1;
    }while((movementAngle>45&&movementAngle<135)||(movementAngle>225&&movementAngle<315));
    xVelocity = 15*cos(movementAngle);
    yVelocity = 15*-sin(movementAngle);

    XPosition = SCREEN_WIDTH/2-20;
    YPosition = SCREEN_HEIGHT/2-20;
}

Ball::~Ball()
{

}

float Ball::getXVelocity()
{
    return xVelocity;
}

float Ball::getYVelocity()
{
    return yVelocity;
}

void Ball::setXVelocity(int newValue)
{
    XVelocity = newValue;
}

void Ball::setYVelocity(int newValue)
{
    YVelocity = newValue;
}

void Ball::horizontalBounce()
{
    xVelocity=-xVelocity;
}

void Ball::verticleBounce()
{
    yVelocity=-yVelocity;
}
