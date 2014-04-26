#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include "GameConfig.h"
#include "Button.h"

class MenuController
{
public:

    MenuController();
    ~MenuController();

    void addButton(Button,buttonEvent);

    void handleEvent(SDL_Event *e);


private:

    std::vector<Button> myButtons;
    std::vector<buttonEvent> myEvents;
};

#endif // MENUCONTROLLER_H
