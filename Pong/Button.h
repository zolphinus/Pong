#ifndef BUTTON_H
#define BUTTON_H

#include "GameConfig.h"

class Button : public GameObject
{
public:

    Button(int x,int y);
    ~Button();

    bool getClicked();
    bool getMouseOver();
    void handleEvent(SDL_Event *);

private:

    int x,y;
    bool isClicked;
    bool mouseOver;

};

#endif // BUTTON_H
