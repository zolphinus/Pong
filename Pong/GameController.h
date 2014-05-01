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

    void applyTexture(GameObject&);


private:
    SDL_Window* gameWindow;
    SDL_Renderer *gameRenderer;
    Uint8 *keystate; //smoother keyboard interactions

    //Game Objects
    Player playerOne;
    Player playerTwo;
    Ball   ball;

    SDL_Event e;

    //draws bounding boxes and collision check lines if true
    bool debugMode;

    //Menu objects
    MenuController mainMenu, pauseMenu;

    //Holds all the game images for reuse
    SDL_Surface* gameImages[IMAGE_LOADED_TOTAL];

    bool quit;


    void initGame();
    void keyboard(Player&, int, int);
    void close();
    void setupObjects();

    void startMultiplayer();


    void initMainMenu();
    void initPauseMenu();

    void drawMainMenu();
    void drawPauseMenu();

    bool collision_point(int, int, GameObject *);
    bool collision_line(int, int, int, int, GameObject *);
    bool place_meeting(int, int, GameObject *, GameObject *);
    double point_distance(int, int, int, int);

    bool loadMedia();
    SDL_Surface* loadSurface(std::string);

};


#endif // GAME_CONTROLLER
