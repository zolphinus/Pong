#include "Paddle.h"

Paddle::Paddle(){
    paddleSurface = NULL;

}

Paddle::~Paddle(){
    SDL_FreeSurface(paddleSurface);
}


SDL_Surface* Paddle::getSurface(){
    return paddleSurface;
}

void Paddle::setSurface(SDL_Surface* newSurface){
    paddleSurface = newSurface;
}
