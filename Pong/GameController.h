#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER
#include "GameConfig.h"
#include <iostream>
#include "MenuController.h"
#include "Button.h"





class GameController{
public:
    GameController();
    ~GameController();
    void runGame();
    void testGame();

    void delay(int);

protected:

    void applySurface(GameObject&);

private:
    SDL_Window* gameWindow;
    SDL_Surface* screenSurface;
    SDL_Surface* backSurface;
    SDL_Surface* currentImage;
    SDL_Surface* tempSurface;
    Uint8 *keystate; //smoother keyboard interactions

    //Game Objects
    Player playerOne;
    Player playerTwo;

    //Menu objects
    MenuController mainMenu, pauseMenu;

    //Holds all the game images for reuse
    SDL_Surface* gameImages[IMAGE_LOADED_TOTAL];

    bool quit;

    void initGame();
    void keyboard(Player&);
    void close();
    void setupObjects();
    void applySurface(GameObject&);


    void initMainMenu();
    void initPauseMenu();

    void drawMainMenu();
    void drawPauseMenu();

    bool loadMedia();
    SDL_Surface* loadSurface(std::string);

};


#endif // GAME_CONTROLLER
