#include "GameController.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;



GameController::GameController() : upPressed(false),downPressed(false),timeCounter(0)
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
    screenSurface = NULL;
    currentImage = NULL;
    tempSurface = NULL;
    quit = false;

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

        gameRenderer = SDL_CreateRenderer(gameWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if( gameWindow == NULL ){
            cout << "Window could not be created! " << SDL_GetError();
        }
        else{
        //Get window surface
        screenSurface = SDL_GetWindowSurface( gameWindow );

        //Fill the surface black
        SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0x00 ) );
        SDL_UpdateWindowSurface( gameWindow );
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
    newButton->setSurface(gameImages[TEST_BUTTON]);
    mainMenu.addButton(newButton,QUIT);
}

void GameController::drawMainMenu()
{
    mainMenu.drawMenu(screenSurface);
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

SDL_Surface* GameController::loadSurface( std::string path )
{

    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        cout << "Unable to load image " << path << endl <<
                "SDL Error: " << SDL_GetError();
    }else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, NULL );
		if( optimizedSurface == NULL )
		{
			cout << "Unable to optimize image " << path << endl << "SDL ERROR : " << SDL_GetError();
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
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
    playerOne.setSurface(gameImages[BLUE_PADDLE]);
    playerOne.gameObjectRect.y = 0;
    playerOne.gameObjectRect.x = SPRITE_SIZE;

    playerOne.setScoreSide(LEFT);
    playerOne.setScore(1, gameImages[NUMBER_ONE]);


    playerTwo.setSurface(gameImages[RED_PADDLE]);
    playerTwo.gameObjectRect.y = 0;
    playerTwo.gameObjectRect.x = SCREEN_WIDTH - 2*SPRITE_SIZE;

//    playerTwo.setScoreSide(RIGHT);

}


void GameController::runGame(){

    //loads a default image to prevent drawing issues should load checks somehow fail. Testing purposes only.
    currentImage = gameImages[RED_PADDLE];

    //Game Loop
    while(quit == false){

        //Input from players
        keyboard(playerOne);

        keyboard(playerTwo);

        SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0x00 ) );

        applySurface(playerOne);
        applySurface(playerTwo);


        /*drawMainMenu();

        /*if(mainMenu.mouseCheck() == QUIT)
        {
            quit = true;
        }*/

        SDL_RenderPresent(gameRenderer);

        //SDL_UpdateWindowSurface(gameWindow);

        /*if(1000 - timeCounter > 17)
        {
            SDL_Delay(17);
            timeCounter += 17;
        }
        else
        {
            SDL_Delay(1000-timeCounter);
            timeCounter = 0;
        }*/
    }
}

void GameController::testGame(){

    //loads a default image to prevent drawing issues should load checks somehow fail. Testing purposes only.
    currentImage = gameImages[RED_PADDLE];

    //Game Loop
    while(quit == false){

        //Input from players
        keyboard(playerOne);

        keyboard(playerTwo);

        SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0x00 ) );

        applySurface(playerOne);
        applySurface(playerTwo);
        applySurface(playerOne.getMyScore());

        SDL_UpdateWindowSurface(gameWindow);
    }
}

void GameController::applySurface(GameObject& updatedObject)
{
    //SDL_BlitSurface(updatedObject.getSurface(), NULL, screenSurface, &updatedObject.gameObjectRect);

}
