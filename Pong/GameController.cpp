#include "GameController.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;



GameController::GameController() : upPressed(false),downPressed(false)
{
    initGame();
}

GameController::~GameController(){
    close();
}

void GameController::close(){

    //Automatically releases memory and stops SDL
    SDL_DestroyWindow( gameWindow );
    SDL_Quit();
}

void GameController::delay(int seconds){

    //Delays
    int milliseconds = seconds * 1000;

    SDL_Delay(milliseconds);

}

void GameController::initGame(){

    gameWindow = NULL;
    quit = false;
    srand(time(NULL));

    //error check for initialization
    if( SDL_Init(SDL_INIT_VIDEO) < 0){

        //printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        cout << "SDL could not initialize! " << SDL_GetError();
    }
    else
    {
                //creating our window
        gameWindow = SDL_CreateWindow("PONG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

        if( gameWindow == NULL )
        {
            cout << "Window could not be created! " << SDL_GetError();
        }
        else
        {
            //Create renderer
            gameRenderer = SDL_CreateRenderer(gameWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            SDL_SetRenderDrawColor(gameRenderer,0x00,0x00,0x00,0xFF);

        }

        bool mediaLoaded = loadMedia();

        if(mediaLoaded == false)
        {
            cout << "ERROR LOADING IMAGES" << endl;
            quit = true;
        }

        setupObjects();
        initMainMenu();
    }
}

void GameController::initMainMenu()
{
    Button *newButton = new Button(0,0);
    newButton->setTexture(gameImages[TEST_BUTTON],gameRenderer);
    mainMenu.addButton(newButton,QUIT);
}

void GameController::drawMainMenu()
{
    mainMenu.drawMenu(gameRenderer);
}

void GameController::keyboard(Player& currentPlayer){
    //Handle events on queue

    SDL_Event e;



    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }
        //User presses a key
        else if( e.type == SDL_KEYDOWN )
        {
            //Select surfaces based on key press
            switch( e.key.keysym.sym )
            {
                case SDLK_UP:
                upPressed = true;
                break;

                case SDLK_DOWN:
                downPressed = true;
                break;

                case SDLK_LEFT:
                break;

                case SDLK_RIGHT:
                break;

                case SDLK_ESCAPE:
                quit = true;
                break;

                default:
                cout << "NOPE" << endl;
                break;
            }

        }
        else if(e.type == SDL_KEYUP)
        {
            switch( e.key.keysym.sym )
            {
                case SDLK_UP:
                upPressed = false;
                break;

                case SDLK_DOWN:
                downPressed = false;
                break;
            }
        }
    }

    if(upPressed)
    {
        currentPlayer.gameObjectRect.y -= 9;
    }

    if(downPressed)
    {
        currentPlayer.gameObjectRect.y += 9;
    }
}
SDL_Surface* GameController::loadSurface(std::string path)
{
    SDL_Surface *loadSurface = SDL_LoadBMP(path.c_str());

    return loadSurface;

}


bool GameController::loadMedia()
{
    //Loading success flag
    bool success = true;


    //Loads images into the Game Images array so that we can reuse them multiple times
    //without needing to re-open the files
    gameImages[BLUE_PADDLE] = loadSurface("images/blue_paddle.bmp");
    if(gameImages[BLUE_PADDLE] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[RED_PADDLE] = loadSurface("images/red_paddle.bmp");
    if(gameImages[RED_PADDLE] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[NUMBER_ONE] = loadSurface("images/red_paddle.bmp");
    if(gameImages[NUMBER_ONE] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[TEST_BUTTON] = loadSurface("images/Green_button.bmp");
    if(gameImages[TEST_BUTTON] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    return success;
}

void GameController::setupObjects(){

    //Initializes starting locations for paddles
    playerOne.setTexture(gameImages[BLUE_PADDLE],gameRenderer);
    playerOne.gameObjectRect.y = 0;
    playerOne.gameObjectRect.x = SPRITE_SIZE;

    playerOne.setScoreSide(LEFT);
    playerOne.setScore(1, gameImages[NUMBER_ONE],gameRenderer);


    playerTwo.setTexture(gameImages[RED_PADDLE],gameRenderer);
    playerTwo.gameObjectRect.y = 0;
    playerTwo.gameObjectRect.x = SCREEN_WIDTH - 2*SPRITE_SIZE;

//    playerTwo.setScoreSide(RIGHT);

}


void GameController::runGame(){

    //loads a default image to prevent drawing issues should load checks somehow fail. Testing purposes only.
//    currentImage = gameImages[RED_PADDLE];

    //Game Loop
    while(quit == false){

        //Input from players
        keyboard(playerOne);

        keyboard(playerTwo);

        SDL_RenderClear(gameRenderer);

        applySurface(playerOne);
        applySurface(playerTwo);

        /*drawMainMenu();

        /*if(mainMenu.mouseCheck() == QUIT)
        {
            quit = true;
        }*/

        SDL_RenderPresent(gameRenderer);

        SDL_Delay(17);
    }
}

void GameController::testGame(){

    //loads a default image to prevent drawing issues should load checks somehow fail. Testing purposes only.
//    currentImage = gameImages[RED_PADDLE];

    //Game Loop
    while(quit == false){

        //Input from players
        keyboard(playerOne);

        keyboard(playerTwo);

//        SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0x00 ) );

        applySurface(playerOne);
        applySurface(playerTwo);
        applySurface(playerOne.getMyScore());

        SDL_UpdateWindowSurface(gameWindow);
    }
}

void GameController::applySurface(GameObject& updatedObject)
{
    SDL_RenderCopy(gameRenderer,updatedObject.getTexture(),NULL,&updatedObject.gameObjectRect);
}
