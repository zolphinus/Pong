#include "GameController.h"

using std::cout;
using std::cin;
using std::endl;



GameController::GameController()
{
    initGame();
}

GameController::~GameController(){
    close();
}

void GameController::close(){

    //Automatically releases memory and stops SDL
    SDL_DestroyWindow(gameWindow);
    SDL_DestroyRenderer(gameRenderer);

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

        int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
        if(IMG_Init(imgFlags) != imgFlags)
        {
            cout << "SDL_image failed to initialize: " << IMG_GetError();
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

SDL_Surface* GameController::loadSurface(std::string path)
{
    SDL_Surface *loadSurface = IMG_Load(path.c_str());

    if( loadSurface == NULL )
    {
        cout << "Unable to load image " << path << endl <<
                "SDL Error: " << IMG_GetError();
    }

    return loadSurface;

}

bool GameController::loadMedia()
{
    //Loading success flag
    bool success = true;


    //Loads images into the Game Images array so that we can reuse them multiple times
    //without needing to re-open the files
    gameImages[BLUE_PADDLE] = loadSurface("images/blue_paddle.png");
    if(gameImages[BLUE_PADDLE] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[RED_PADDLE] = loadSurface("images/red_paddle.bmp");
    if(gameImages[RED_PADDLE] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[NUMBER_ZERO] = loadSurface("images/zero.bmp");
    if(gameImages[NUMBER_ZERO] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[NUMBER_ONE] = loadSurface("images/one.bmp");
    if(gameImages[NUMBER_ONE] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[NUMBER_TWO] = loadSurface("images/two.bmp");
    if(gameImages[NUMBER_TWO] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[NUMBER_THREE] = loadSurface("images/three.bmp");
    if(gameImages[NUMBER_THREE] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[NUMBER_FOUR] = loadSurface("images/four.bmp");
    if(gameImages[NUMBER_FOUR] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[NUMBER_FIVE] = loadSurface("images/five.bmp");
    if(gameImages[NUMBER_FIVE] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[NUMBER_SIX] = loadSurface("images/six.bmp");
    if(gameImages[NUMBER_SIX] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[NUMBER_SEVEN] = loadSurface("images/seven.bmp");
    if(gameImages[NUMBER_SEVEN] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[NUMBER_EIGHT] = loadSurface("images/eight.bmp");
    if(gameImages[NUMBER_EIGHT] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[NUMBER_NINE] = loadSurface("images/nine.bmp");
    if(gameImages[NUMBER_NINE] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[TEST_BUTTON] = loadSurface("images/Green_button.bmp");
    if(gameImages[TEST_BUTTON] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[BALL] = loadSurface("images/ball.bmp");
    if(gameImages[BALL] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    return success;
}

void GameController::setupObjects(){

    //Initializes starting locations for paddles
    playerOne.setTexture(gameImages[BLUE_PADDLE],gameRenderer);
    playerOne.gameObjectRect.y = (SCREEN_HEIGHT / 2) - (playerOne.gameObjectRect.h /2);
    playerOne.gameObjectRect.x = SPRITE_SIZE;

    playerOne.setScoreSide(LEFT);
    playerOne.setScore(0, gameImages[NUMBER_ZERO],gameRenderer);


    playerTwo.setTexture(gameImages[RED_PADDLE],gameRenderer);
    playerTwo.gameObjectRect.y = (SCREEN_HEIGHT / 2) - (playerOne.gameObjectRect.h /2);
    playerTwo.gameObjectRect.x = SCREEN_WIDTH - 2*SPRITE_SIZE;

    playerTwo.setScoreSide(RIGHT);
    playerTwo.setScore(0, gameImages[NUMBER_ZERO],gameRenderer);


    ball.setTexture(gameImages[BALL], gameRenderer);
    ball.gameObjectRect.y = SCREEN_HEIGHT/2 - ball.gameObjectRect.h/2;
    ball.gameObjectRect.x = SCREEN_WIDTH/2 - ball.gameObjectRect.w/2;
}

void GameController::runGame()
{
    //Game Loop
    while(quit == false)
    {
        startMultiplayer();
    }
}

void GameController::applyTexture(GameObject& updatedObject)
{
    SDL_RenderCopy(gameRenderer,updatedObject.getTexture(),NULL,&updatedObject.gameObjectRect);
}

void GameController::startMultiplayer()
{
    while(quit == false)
    {
        //Input from players

        SDL_RenderClear(gameRenderer);

        //First player actions
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            //User presses a key
            else if( e.type == SDL_KEYDOWN)
            {
                if( e.key.keysym.sym  == SDLK_UP)
                {
                    playerOne.setUpPressed(true);
                }

                if( e.key.keysym.sym  == SDLK_DOWN)
                {
                    playerOne.setDownPressed(true);
                }

                if( e.key.keysym.sym  == SDLK_ESCAPE)
                {
                    quit = true;
                }
            }
            else if(e.type == SDL_KEYUP)
            {
                if( e.key.keysym.sym  == SDLK_UP)
                {
                    playerOne.setUpPressed(false);
                }

                if( e.key.keysym.sym  == SDLK_DOWN)
                {
                    playerOne.setDownPressed(false);
                }
            }

        //second player actions
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            //User presses a key
            else if( e.type == SDL_KEYDOWN)
            {
                if( e.key.keysym.sym  == SDLK_w)
                {
                    playerTwo.setUpPressed(true);
                }

                if( e.key.keysym.sym  == SDLK_s)
                {
                    playerTwo.setDownPressed(true);
                }

                if( e.key.keysym.sym  == SDLK_ESCAPE)
                {
                    quit = true;
                }
            }
            else if(e.type == SDL_KEYUP)
            {
                if( e.key.keysym.sym  == SDLK_w)
                {
                    playerTwo.setUpPressed(false);
                }

                if( e.key.keysym.sym  == SDLK_s)
                {
                    playerTwo.setDownPressed(false);
                }
            }
        }//while


    if(playerOne.getUpPressed() == true)
    {
        playerOne.gameObjectRect.y -= 9;
    }

    if(playerOne.getDownPressed() == true)
    {
        playerOne.gameObjectRect.y += 9;
    }

    if(playerTwo.getUpPressed() == true)
    {
        playerTwo.gameObjectRect.y -= 9;
    }

    if(playerTwo.getDownPressed() == true)
    {
        playerTwo.gameObjectRect.y += 9;
    }


    if(playerOne.gameObjectRect.y < 0)
    {
        playerOne.gameObjectRect.y = 0;
    }

    if(playerOne.gameObjectRect.y > (SCREEN_HEIGHT - playerOne.gameObjectRect.h))
    {
        playerOne.gameObjectRect.y = (SCREEN_HEIGHT - playerOne.gameObjectRect.h);
    }

    if(playerTwo.gameObjectRect.y < 0)
    {
        playerTwo.gameObjectRect.y = 0;
    }

    if(playerTwo.gameObjectRect.y > (SCREEN_HEIGHT - playerOne.gameObjectRect.h))
    {
        playerTwo.gameObjectRect.y = (SCREEN_HEIGHT - playerOne.gameObjectRect.h);
    }

    //Score stuff for testing
    //playerOne.setScore(1, gameImages[NUMBER_ONE], gameRenderer);
    //playerTwo.setScore(1, gameImages[NUMBER_ONE], gameRenderer);

        applyTexture(playerOne);
        applyTexture(playerTwo);
        applyTexture(playerOne.getMyScore());
        applyTexture(playerTwo.getMyScore());


        SDL_RenderPresent(gameRenderer);
    }

}

bool GameController::place_meeting(int checkX, int checkY, GameObject startObject, GameObject checkObject)
{
    SDL_Rect startRect = startObject.gameObjectRect;
    if(collision_line(startRect.x,startRect.y,startRect.x+startRect.w,startRect.y,checkObject) || //top line
       collision_line(startRect.x,startRect.y,startRect.x,startRect.y+startRect.h,checkObject) || //left line
       collision_line(startRect.x+startRect.w,startRect.y,startRect.x+startRect.w,startRect.y+startRect.h,checkObject) || //right line
       collision_line(startRect.x,startRect.y+startRect.h,startRect.x+startRect.w,startRect.y+startRect.h,checkObject))//bottom line
    {
        return true;
    }

    return false;
}

bool GameController::collision_line(int startX, int startY, int endX, int endY, GameObject checkObject)
{
    double checkAngle = atan2(endX-startX,endY-startY);
    int checkDistance = point_distance(startX,startY,endX,endY);
    cout << "Angle: " << checkAngle << endl;
    cout << "Distance: " << checkDistance << endl;
    return false;
}

bool GameController::collision_point(int checkX, int checkY, GameObject checkObject)
{
    SDL_Rect checkRect = checkObject.gameObjectRect;

    if(checkX > checkRect.x && checkX < checkRect.x + checkRect.w && checkY > checkRect.y && checkY < checkRect.y + checkRect.h)
    {
        return true;
    }

    return false;
}

double GameController::point_distance(int x1, int y1, int x2, int y2)
{
    double distance = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    return distance;
}
