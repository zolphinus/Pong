#include "Button.h"

Button::Button(int x, int y)
{
    this -> x = x;
    this -> y = y;

    isClicked = false;
    mouseOver = false;
}

Button::~Button()
{

}

bool Button::getClicked()
{
    return isClicked;
}

bool Button::getMouseOver()
{
    return mouseOver;
}

void handleEvent(SDL_Event *event)
{

}
