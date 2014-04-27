#include "MenuController.h"

MenuController::MenuController()
{

}

MenuController::~MenuController()
{

}

void MenuController::addButton(Button *newButton, buttonEvent newEvent)
{
    myButtons.push_back(newButton);
    myEvents.push_back(newEvent);
}

buttonEvent MenuController::handleEvent(SDL_Event *event)
{
    for(int i = 0;i<myButtons.size();i++)
    {
        myButtons.at(i)->handleEvent(event);
        if(myButtons.at(i)->getClicked())
        {
            std::cout << "Clicked button." << std::endl;
        }
    }
}

void MenuController::drawMenu(SDL_Surface *surf)
{
    for(int i = 0;i<myButtons.size();i++)
    {
        SDL_BlitSurface(myButtons.at(i)->getSurface(), NULL, surf, &myButtons.at(i)->gameObjectRect);
    }
}
