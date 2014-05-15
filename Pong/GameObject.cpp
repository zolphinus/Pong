#include "GameObject.h"
#include <iostream>

GameObject::GameObject(){
    gameObjectTexture = NULL;

}

GameObject::~GameObject(){
    SDL_DestroyTexture(gameObjectTexture);
}


SDL_Texture* GameObject::getTexture(){
    return gameObjectTexture;
}

void GameObject::setTexture(SDL_Surface *newSurface,SDL_Renderer *renderer)
{
    if(gameObjectTexture != NULL)
    {
        SDL_DestroyTexture(gameObjectTexture);
    }
    gameObjectTexture = SDL_CreateTextureFromSurface(renderer,newSurface);
    gameObjectRect.w = newSurface -> w;
    gameObjectRect.h = newSurface -> h;
}

