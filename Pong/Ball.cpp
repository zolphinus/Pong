#include "Ball.h"

Ball::Ball()
{
    setXVelocity(rand()%10+10);
    setYVelocity(rand()%10+10);
}

Ball::~Ball()
{

}

int Ball::getXVelocity()
{
    return XVelocity;
}

int Ball::getYVelocity()
{
    return YVelocity;
}

int Ball::getXPosition()
{
    return XPosition;
}

int Ball::getYPosition()
{
    return YPosition;
}

void Ball::setXVelocity(int newValue)
{
    XVelocity = newValue;
}

void Ball::setYVelocity(int newValue)
{
    YVelocity = newValue;
}

void Ball::setXPosition(int newValue)
{
    XPosition=newValue;
}

void Ball::setYPosition(int newValue)
{
    YPosition=newValue;
}

void Ball::bounce()
{
    XVelocity=-XVelocity;
}
