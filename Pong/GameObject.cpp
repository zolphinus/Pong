#include "GameObject.h"
#include <iostream>

GameObject::GameObject(){
    gameObjectSurface = NULL;

}

GameObject::~GameObject(){
    SDL_FreeSurface(gameObjectSurface);
}


SDL_Surface* GameObject::getSurface(){
    return gameObjectSurface;
}

void GameObject::setSurface(SDL_Surface* newSurface){
    gameObjectSurface = newSurface;
    gameObjectRect.w = newSurface -> w;
    gameObjectRect.h = newSurface -> h;
    std::cout << gameObjectRect.w << std::endl;
    std::cout << gameObjectRect.h << std::endl;
}

