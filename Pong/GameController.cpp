#include "GameController.h"
#include <iostream>
#include <SDL.h>

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
    SDL_DestroyWindow( gameWindow );
    SDL_Quit();
}

void GameController::delay(int seconds){
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
                            currentPlayer.paddleRect.y -= 9;
                            break;

                            case SDLK_DOWN:
                            currentPlayer.paddleRect.y += 9;
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
    playerOne.setSurface(gameImages[BLUE_PADDLE]);
    playerOne.paddleRect.y = 0;
    playerOne.paddleRect.x = SPRITE_SIZE;


    playerTwo.paddleRect.y = 0;
    playerTwo.paddleRect.x = SCREEN_WIDTH - SPRITE_SIZE;

    playerTwo.setSurface(gameImages[RED_PADDLE]);


}


void GameController::runGame(){

    currentImage = gameImages[RED_PADDLE];
    while(quit == false){
        keyboard(playerOne);

        SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0x00 ) );
        SDL_BlitSurface(playerOne.getSurface(), NULL, screenSurface, &playerOne.paddleRect);


        SDL_BlitSurface(playerTwo.getSurface(), NULL, screenSurface, &playerTwo.paddleRect);

        SDL_UpdateWindowSurface(gameWindow);
    }
}
