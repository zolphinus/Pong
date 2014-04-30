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
    void setScoreImage(SDL_Surface *,SDL_Renderer *);
    void resetScore();
    void setTexture(SDL_Surface *,SDL_Renderer *);

    SDL_Texture* getScoreImage();
    int getScoreValue();

private:
    int scoreValue;


};

#endif // SCORE

