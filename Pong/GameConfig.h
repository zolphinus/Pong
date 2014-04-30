#ifndef GAME_CONFIG
#define GAME_CONFIG

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SPRITE_SIZE = 32;

#include <vector>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <ctime>

enum ImagesLoaded
{
    //As we add images, add the appropriate image names just before IMAGE_LOADED_TOTAL so that
    //it doesn't break any current systems but extends what we can load/draw
    BLUE_PADDLE,
    RED_PADDLE,
    TEST_BUTTON,
    NUMBER_ZERO,
    NUMBER_ONE,
    NUMBER_TWO,
    NUMBER_THREE,
    NUMBER_FOUR,
    NUMBER_FIVE,
    NUMBER_SIX,
    NUMBER_SEVEN,
    NUMBER_EIGHT,
    NUMBER_NINE,
    BALL,
    IMAGE_LOADED_TOTAL
};

enum AI
{
    IS_AN_AI,
    IS_NOT_AI
};

enum Score_Side
{
    LEFT,
    RIGHT
};


enum buttonEvent
{
    //Add events here as needed
    NONE,
    QUIT,
    RESUME,
    START_AI,
    START_PVP,
    MAIN_MENU

};

#include "GameObject.h"
#include "Score.h"
#include "Player.h"
#include "Ball.h"



#endif // GAME_CONFIG
