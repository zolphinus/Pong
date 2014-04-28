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

buttonEvent MenuController::mouseCheck()
{
    buttonEvent currentEvent = NONE;
    for(int i = 0;i<myButtons.size();i++)
    {
        myButtons.at(i)->mouseCheck();
        if(myButtons.at(i)->getClicked())
        {
            std::cout << "Clicked button." << std::endl;
            currentEvent = myEvents.at(i);
        }
    }

    return currentEvent;
}

void MenuController::drawMenu(SDL_Surface *surf)
{
    for(int i = 0;i<myButtons.size();i++)
    {
        SDL_BlitSurface(myButtons.at(i)->getSurface(), NULL, surf, &myButtons.at(i)->gameObjectRect);
    }
}
