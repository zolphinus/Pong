#ifndef PLAYER
#define PLAYER
#include "GameConfig.h"
#include "Score.h"


class Player : public GameObject
{
public:
    Player();
    ~Player();
    void setAI(AI);
    void setScore(int value, SDL_Surface* scoreImage);
    int getScoreValue();
    SDL_Surface* getScoreImage();



private:
    bool isAI;
    Score myScore;


};

#endif // Player
