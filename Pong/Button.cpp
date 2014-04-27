#include "Button.h"

Button::Button(int x, int y)
{
    gameObjectRect.x = x;
    gameObjectRect.y = y;

    isClicked = false;
    mouseOver = false;

    std::cout << "Button made" << std::endl;
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

void Button::handleEvent(SDL_Event *event)
{
    isClicked = false;
    mouseOver = false;

    int mouseX,mouseY, buttonState;


    buttonState = SDL_GetMouseState(&mouseX,&mouseY);

    if(mouseX > gameObjectRect.x && mouseX < gameObjectRect.x + gameObjectRect.w && mouseY > gameObjectRect.y && mouseY < gameObjectRect.y + gameObjectRect.h)
    {
        mouseOver = true;
        if(buttonState == 1)
        {
            isClicked = true;
        }
    }
}
