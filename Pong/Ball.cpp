#include "Ball.h"

Ball::Ball()
{
    resetBall();
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
    xVelocity = newValue;
}

void Ball::setYVelocity(int newValue)
{
    yVelocity = newValue;
}

void Ball::horizontalBounce()
{
    xVelocity=-xVelocity;
    movementAngle = atan2(yVelocity,xVelocity);
    velocity += 0.25;
    calcVelocities();
}

void Ball::verticalBounce()
{
    yVelocity=-yVelocity;
    movementAngle = atan2(yVelocity,xVelocity);
    calcVelocities();
}

void Ball::resetBall()
{
    velocity = rand() % 5 + 8;
    int side = rand() % 2;

    int tempAngle = 0;
    double movementAngle = 0;
    if(side == 0)
    {
        tempAngle = 45 - (rand() % 91);
    }
    else
    {
        tempAngle = (rand() % 91) + 135;
    }

    movementAngle = tempAngle*(3.1415926/180);

    xVelocity = velocity*cos(movementAngle);
    yVelocity = velocity*-sin(movementAngle);

    xPosition = SCREEN_WIDTH/2-gameObjectRect.w/2;
    yPosition = SCREEN_HEIGHT/2-gameObjectRect.h/2;

    gameObjectRect.x = xPosition;
    gameObjectRect.y = yPosition;
}

void Ball::calcVelocities()
{
    xVelocity = velocity*cos(movementAngle);
    yVelocity = velocity*sin(movementAngle);
}
