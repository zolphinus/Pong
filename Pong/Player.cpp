#include "Player.h"

Player::Player(){
    isAI = false;
}

Player::~Player(){

}


void Player::setAI(AI checkForAI)
{
    if(checkForAI == IS_AN_AI)
    {
        isAI = true;
    }
    else
    {
        isAI = false;
    }
}


void Player::resetScore()
{
    myScore.resetScore();
}

void Player::setScoreSide(Score_Side newSide)
{
    myScore.setSide(newSide);
}

void Player::setScore(int newValue, SDL_Surface* newScoreImage,SDL_Renderer *renderer){

    myScore.setScoreValue(newValue);
    myScore.setScoreImage(newScoreImage,renderer);
}

int Player::getScoreValue()
{
    return myScore.getScoreValue();
}

SDL_Texture* Player::getScoreImage()
{
    return myScore.getScoreImage();
}

Score& Player::getMyScore()
{
    return myScore;
}


