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

    void resetScore();
    void setScoreSide(Score_Side);
    void setScore(int value, SDL_Surface* scoreImage);

    int getScoreValue();
    SDL_Surface* getScoreImage();
    Score& getMyScore();



private:
    bool isAI;
    Score myScore;


};

#endif // Player
