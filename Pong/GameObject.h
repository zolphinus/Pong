#ifndef GAME_OBJECT
#define GAME_OBJECT
#include <SDL.h>


//Balls, paddles, scores, walls can use this setup

class GameObject{
public:
    GameObject();
    ~GameObject();
    SDL_Surface* getSurface();
    void setSurface(SDL_Surface*);
    SDL_Rect gameObjectRect;

private:
    SDL_Surface* gameObjectSurface;

};



#endif // GAME_OBJECT


