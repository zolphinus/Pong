#include "GameConfig.h"

Score::Score(){
    resetScore();
}

Score::~Score(){
}

void Score::resetScore()
{
    scoreValue = 0;
    SDL_DestroyTexture(gameObjectTexture);
    gameObjectTexture = NULL;
}

void Score::setScoreValue(int newScore)
{
    this->scoreValue = newScore;
}

int Score::getScoreValue()
{
    return scoreValue;
}


void Score::setScoreImage(SDL_Surface* newScore ,SDL_Renderer *renderer)
{
    Score::setTexture(newScore,renderer);
}

SDL_Texture* Score::getScoreImage()
{
    return GameObject::getTexture();
}

void Score::setSide(Score_Side newSide)
{
    if(newSide == LEFT)
    {
        //SET SCORE COORDINATES TO DISPLAY ON LEFT SIDE
        gameObjectRect.y = (SPRITE_SIZE / 2);
        gameObjectRect.x = (SCREEN_WIDTH / 2) - 4*SPRITE_SIZE;

    }
    else if(newSide == RIGHT)
    {
        //SET SCORE COORDINATES TO DISPLAY ON THE RIGHT SIDE
        gameObjectRect.y = (SPRITE_SIZE / 2);
        gameObjectRect.x = (SCREEN_WIDTH / 2) + 2*SPRITE_SIZE;
    }
}


void Score::setTexture(SDL_Surface *newSurface,SDL_Renderer *renderer)
{
    if(gameObjectTexture != NULL)
    {
        SDL_DestroyTexture(gameObjectTexture);
    }
    gameObjectTexture = SDL_CreateTextureFromSurface(renderer,newSurface);
    gameObjectRect.w = 64;
    gameObjectRect.h = 64;
}
