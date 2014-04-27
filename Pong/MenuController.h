#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include "GameConfig.h"
#include "Button.h"

class MenuController
{
public:

    MenuController();
    ~MenuController();

    void addButton(Button*,buttonEvent);

    buttonEvent handleEvent(SDL_Event *);

    void drawMenu(SDL_Surface *);


private:

    std::vector<Button*> myButtons;
    std::vector<buttonEvent> myEvents;
};

#endif // MENUCONTROLLER_H
