#ifndef PLAYER
#define PLAYER
#include "GameConfig.h"
#include "Score.h"

class PowerUp;


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

    void pickedUp(PowerUp& currentItem);

    bool getPowerUpState(powerUpType);



    int getScoreValue();
    SDL_Texture* getScoreImage();
    Score& getMyScore();





private:
    bool isAI;
    Score myScore;
    bool upPressed,downPressed;
    std::vector <bool> powerUpState;

    int powerUpDuration;

};

#endif // Player
