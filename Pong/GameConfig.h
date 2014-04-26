#ifndef GAME_CONFIG
#define GAME_CONFIG

enum ImagesLoaded
{
    //As we add images, add the appropriate image names just before IMAGE_LOADED_TOTAL so that
    //it doesn't break any current systems but extends what we can load/draw
    BLUE_PADDLE,
    RED_PADDLE,
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

#include <SDL.h>
#include "GameObject.h"
#include "Player.h"
#include "Score.h"


#endif // GAME_CONFIG
