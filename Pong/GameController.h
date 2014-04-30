#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER
#include "GameConfig.h"
#include "MenuController.h"





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
    SDL_Renderer *gameRenderer;
    Uint8 *keystate; //smoother keyboard interactions

    //Game Objects
    Player playerOne;
    Player playerTwo;

    //Menu objects
    MenuController mainMenu, pauseMenu;

    //Holds all the game images for reuse
    SDL_Surface* gameImages[IMAGE_LOADED_TOTAL];

    bool quit;

    bool upPressed,downPressed;

    void initGame();
    void keyboard(Player&);
    void close();
    void setupObjects();


    void initMainMenu();
    void initPauseMenu();

    void drawMainMenu();
    void drawPauseMenu();

    bool collision_point(int, int, GameObject);
    bool collision_line(int, int, int, int, GameObject);
    bool place_meeting(int, int, GameObject, GameObject);
    double point_distance(int, int, int, int);

    bool loadMedia();
    SDL_Surface* loadSurface(std::string);

};


#endif // GAME_CONTROLLER
