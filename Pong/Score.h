#ifndef SCORE
#define SCORE

#include <SDL.h>
//#include "GameConfig.h"
//#include "GameObject.h"


class Score : public GameObject
{
public:
    Score();
    ~Score();
    void setSide(Score_Side); //Sets which side of the field the score can display to
    void setScoreValue(int newScore);
    void setScoreImage(SDL_Surface* newScore);
    void resetScore();

    SDL_Surface* getScoreImage();
    int getScoreValue();

private:
    int scoreValue;


};

#endif // SCORE

