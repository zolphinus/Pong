#include "GameObject.h"


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
}

