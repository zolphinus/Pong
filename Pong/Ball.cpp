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

void Ball::setXVelocity(int newValue)
{
    XVelocity = newValue;
}

void Ball::setYVelocity(int newValue)
{
    YVelocity = newValue;
}

void Ball::bounce()
{
    XVelocity=-XVelocity;
}
