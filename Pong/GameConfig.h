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

#include "GameObject.h"
#include "Paddle.h"


#endif // GAME_CONFIG
