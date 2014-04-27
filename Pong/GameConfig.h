#ifndef GAME_CONFIG
#define GAME_CONFIG

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SPRITE_SIZE = 32;

#include <vector>
#include <iostream>
#include <SDL.h>

enum ImagesLoaded
{
    //As we add images, add the appropriate image names just before IMAGE_LOADED_TOTAL so that
    //it doesn't break any current systems but extends what we can load/draw
    BLUE_PADDLE,
    RED_PADDLE,
    TEST_BUTTON,
    NUMBER_ONE,
    IMAGE_LOADED_TOTAL
};

enum AI
{
    //As we add images, add the appropriate image names just before IMAGE_LOADED_TOTAL so that
    //it doesn't break any current systems but extends what we can load/draw
    IS_AN_AI,
    IS_NOT_AI
};

enum Score_Side
{
    //As we add images, add the appropriate image names just before IMAGE_LOADED_TOTAL so that
    //it doesn't break any current systems but extends what we can load/draw
    LEFT,
    RIGHT
};


enum buttonEvent
{
    QUIT,
    RESUME,
    START_AI,
    START_PVP,
    MAIN_MENU

};

#include "GameObject.h"
#include "Score.h"
#include "Player.h"



#endif // GAME_CONFIG
