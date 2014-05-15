#ifndef GAME_OBJECT
#define GAME_OBJECT

#include <SDL.h>

//Balls, paddles, scores, walls can use this setup

class GameObject{
public:
    GameObject();
    ~GameObject();
    SDL_Texture* getTexture();
    void setTexture(SDL_Surface *,SDL_Renderer *);
    SDL_Rect gameObjectRect;

protected:
    SDL_Texture* gameObjectTexture;

};



#endif // GAME_OBJECT


