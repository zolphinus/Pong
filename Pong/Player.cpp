#include "Player.h"
#include "PowerUp.h"

Player::Player(){
    isAI = false;
    upPressed = false;
    downPressed = false;
    powerUpState.resize(TOTAL_POWER_UPS);
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

void Player::setDownPressed(bool newPress)
{
    this->downPressed = newPress;
}

void Player::setUpPressed(bool newPress)
{
    this->upPressed = newPress;
}

bool Player::getDownPressed()
{
    return this->downPressed;
}

bool Player::getUpPressed()
{
    return this->upPressed;
}

void Player::pickedUp(PowerUp& currentItem){
    currentItem.pickedUp();
}



bool Player::getPowerUpState(powerUpType getValue)
{
    return powerUpState[getValue];
}
