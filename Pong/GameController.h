#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER
#include <SDL.h>
#include <iostream>
#include "Paddle.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SPRITE_SIZE = 32;

enum ImagesLoaded
{
    BLUE_PADDLE,
    RED_PADDLE,
    IMAGE_LOADED_TOTAL
};


class GameController{
public:
    GameController();
    ~GameController();
    void runGame();

    void delay(int);


private:
    SDL_Window* gameWindow;
    SDL_Surface* screenSurface;
    SDL_Surface* backSurface;
    SDL_Surface* currentImage;
    SDL_Surface* tempSurface;
    Uint8 *keystate; //smoother keyboard interactions

    Paddle playerOne;
    Paddle playerTwo;


    //Holds all the game images for reuse
    SDL_Surface* gameImages[IMAGE_LOADED_TOTAL];

    SDL_Event e;
    bool quit;

    void initGame();
    void keyboard(Paddle&);
    void close();
    void setupPaddles();
    bool loadMedia();
    SDL_Surface* loadSurface(std::string);


};


#endif // GAME_CONTROLLER