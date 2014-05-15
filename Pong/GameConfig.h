#ifndef GAME_CONFIG
#define GAME_CONFIG

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SPRITE_SIZE = 32;


//A rate of one 1 or 0 is a 100% spawn on hit
const int POWER_UP_RATE = 0;

#include <vector>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <SDL_mixer.h>

enum ImagesLoaded
{
    //As we add images, add the appropriate image names just before IMAGE_LOADED_TOTAL so that
    //it doesn't break any current systems but extends what we can load/draw
    BLUE_PADDLE,
    RED_PADDLE,
    SINGLE_BUTTON,
    MULTI_BUTTON,
    RESUME_BUTTON,
    MAIN_MENU_BUTTON,
    EASY_BUTTON,
    MEDIUM_BUTTON,
    HARD_BUTTON,
    P1_WIN_SPLASH,
    P2_WIN_SPLASH,
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
    VELOCITY_POWER,
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

enum Last_Hit
{
    PLAYER_ONE,
    PLAYER_TWO
};


enum buttonEvent
{
    //Add events here as needed
    NONE,
    QUIT,
    RESUME,
    START_AI,
    START_PVP,
    EASY_PICKED,
    MEDIUM_PICKED,
    HARD_PICKED,
    MAIN_MENU

};

enum powerUpType
{
    //Test Item is required as a default to test item generation values
    TEST_ITEM,

    BLUE_SHELL,
    TOTAL_POWER_UPS
};

#include "GameObject.h"
#include "Score.h"
#include "Player.h"
#include "Ball.h"



#endif // GAME_CONFIG
