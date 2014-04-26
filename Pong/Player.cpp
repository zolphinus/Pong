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
