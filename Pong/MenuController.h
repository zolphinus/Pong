#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include "GameConfig.h"
#include "Button.h"

class MenuController
{
public:

    MenuController();
    ~MenuController();

    //add a button to the menu's list of buttons
    void addButton(Button*,buttonEvent);

    //Checks whether a button was clicked, and if it was, returns the action type associated with that button
    buttonEvent mouseCheck();

    void drawMenu(SDL_Renderer *);


private:

    std::vector<Button*> myButtons;
    std::vector<buttonEvent> myEvents;
};

#endif // MENUCONTROLLER_H
