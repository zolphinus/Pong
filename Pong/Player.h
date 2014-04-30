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
    void setScore(int value, SDL_Surface* scoreImage,SDL_Renderer *);
    void setUpPressed(bool);
    void setDownPressed(bool);
    bool getUpPressed();
    bool getDownPressed();


    int getScoreValue();
    SDL_Texture* getScoreImage();
    Score& getMyScore();




private:
    bool isAI;
    Score myScore;
    bool upPressed,downPressed;

};

#endif // Player
