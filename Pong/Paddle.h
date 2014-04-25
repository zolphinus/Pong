#ifndef PADDLE
#define PADDLE
#include <SDL.h>


class Paddle{
public:
    Paddle();
    ~Paddle();
    SDL_Surface* getSurface();
    void setSurface(SDL_Surface*);
    SDL_Rect paddleRect;

private:
    SDL_Surface* paddleSurface;

};

#endif // PADDLE
