#include "GameConfig.h"

Score::Score(){
    resetScore();
}

Score::~Score(){
}

void Score::resetScore()
{
    scoreValue = 0;
    GameObject::setSurface(NULL);
}

void Score::setScoreValue(int newScore)
{
    this->scoreValue = newScore;
}

int Score::getScoreValue()
{
    return scoreValue;
}


void Score::setScoreImage(SDL_Surface* newScore)
{
    GameObject::setSurface(newScore);
}

SDL_Surface* Score::getScoreImage()
{
    return GameObject::getSurface();
}

void Score::setSide(Score_Side newSide)
{
    if(newSide == LEFT)
    {
        //SET SCORE COORDINATES TO DISPLAY ON LEFT SIDE
        gameObjectRect.y = 200;
        gameObjectRect.x = 50;

    }
    else if(newSide == RIGHT)
    {
        //SET SCORE COORDINATES TO DISPLAY ON THE RIGHT SIDE
        gameObjectRect.y = 200;
        gameObjectRect.x = SCREEN_WIDTH - 100;
    }
}
