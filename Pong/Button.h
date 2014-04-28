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

    void mouseCheck();

private:

    bool isClicked;
    bool mouseOver;

};

#endif // BUTTON_H
