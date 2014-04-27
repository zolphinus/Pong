#include "GameController.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;



GameController::GameController(){
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

        setupPaddles();
    }
}


void GameController::keyboard(Paddle& currentPlayer){
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
        else


            if( e.type == SDL_KEYDOWN )
        {
            //Select surfaces based on key press
            switch( e.key.keysym.sym )
            {
                case SDLK_UP:
                currentPlayer.gameObjectRect.y -= 9;
                break;

                case SDLK_DOWN:
                currentPlayer.gameObjectRect.y += 9;
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

    return success;
}

void GameController::setupPaddles(){

    //Initializes starting locations for paddles
    playerOne.setSurface(gameImages[BLUE_PADDLE]);
    playerOne.gameObjectRect.y = 0;
    playerOne.gameObjectRect.x = SPRITE_SIZE;


    playerTwo.gameObjectRect.y = 0;
    playerTwo.gameObjectRect.x = SCREEN_WIDTH - SPRITE_SIZE;

    playerTwo.setSurface(gameImages[RED_PADDLE]);


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

        SDL_UpdateWindowSurface(gameWindow);
    }
}

void GameController::applySurface(GameObject& updatedObject)
{
    SDL_BlitSurface(updatedObject.getSurface(), NULL, screenSurface, &updatedObject.gameObjectRect);
}
