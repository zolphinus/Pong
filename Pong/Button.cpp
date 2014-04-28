#include "Button.h"

Button::Button(int x, int y)
{
    gameObjectRect.x = x;
    gameObjectRect.y = y;

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

void Button::mouseCheck()
{
    int mouseX,mouseY, buttonState;

    buttonState = SDL_GetMouseState(&mouseX,&mouseY);

    if(mouseX > gameObjectRect.x && mouseX < gameObjectRect.x + gameObjectRect.w
       && mouseY > gameObjectRect.y && mouseY < gameObjectRect.y + gameObjectRect.h) //Mouse is on the button
    {
        mouseOver = true;
        if(buttonState == 1)//left button down
        {
            isClicked = true;
        }
        else
        {
            isClicked = false;
        }
    }
    else
    {
        mouseOver = false;
        isClicked = false;
    }
}
