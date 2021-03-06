#include "GameController.h"
#include "GameConfig.h"

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
    debugMode = false;
    seizureMode = false;
    srand(time(NULL));
    AISpeedCap = 3;

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
        initPauseMenu();
        initDiffMenu();
    }
}

void GameController::initMainMenu()
{
    int prevButtonHeight = 0;
    Button *newButton = new Button(0,0);
    newButton->setTexture(gameImages[MULTI_BUTTON],gameRenderer);
    newButton->gameObjectRect.x = SCREEN_WIDTH/2 - newButton->gameObjectRect.w/2;
    newButton->gameObjectRect.y = SCREEN_HEIGHT/2;
    mainMenu.addButton(newButton,START_PVP);

    prevButtonHeight = newButton->gameObjectRect.h;

    newButton = new Button(0,0);
    newButton->setTexture(gameImages[SINGLE_BUTTON],gameRenderer);
    newButton->gameObjectRect.x = SCREEN_WIDTH/2 - newButton->gameObjectRect.w/2;
    newButton->gameObjectRect.y = SCREEN_HEIGHT/2+prevButtonHeight+16;
    mainMenu.addButton(newButton,START_AI);

    prevButtonHeight = prevButtonHeight+16+newButton->gameObjectRect.h;
}

void GameController::initPauseMenu()
{
    int prevButtonHeight = 0;
    Button *newButton = new Button(0,0);
    newButton->setTexture(gameImages[MAIN_MENU_BUTTON],gameRenderer);
    newButton->gameObjectRect.x = SCREEN_WIDTH/2 - newButton->gameObjectRect.w/2;
    newButton->gameObjectRect.y = SCREEN_HEIGHT/2;
    pauseMenu.addButton(newButton,MAIN_MENU);

    prevButtonHeight = newButton->gameObjectRect.h;

    newButton = new Button(0,0);
    newButton->setTexture(gameImages[RESUME_BUTTON],gameRenderer);
    newButton->gameObjectRect.x = SCREEN_WIDTH/2 - newButton->gameObjectRect.w/2;
    newButton->gameObjectRect.y = SCREEN_HEIGHT/2+prevButtonHeight+16;
    pauseMenu.addButton(newButton,RESUME);

    prevButtonHeight = prevButtonHeight+16+newButton->gameObjectRect.h;
}

void GameController::initDiffMenu()
{
    int prevButtonHeight = 0;
    Button *newButton = new Button(0,0);
    newButton->setTexture(gameImages[EASY_BUTTON],gameRenderer);
    newButton->gameObjectRect.x = SCREEN_WIDTH/2 - newButton->gameObjectRect.w/2;
    newButton->gameObjectRect.y = SCREEN_HEIGHT/2;
    diffMenu.addButton(newButton,EASY_PICKED);

    prevButtonHeight = newButton->gameObjectRect.h;

    newButton = new Button(0,0);
    newButton->setTexture(gameImages[MEDIUM_BUTTON],gameRenderer);
    newButton->gameObjectRect.x = SCREEN_WIDTH/2 - newButton->gameObjectRect.w/2;
    newButton->gameObjectRect.y = SCREEN_HEIGHT/2+prevButtonHeight+16;
    diffMenu.addButton(newButton,MEDIUM_PICKED);

    prevButtonHeight = prevButtonHeight+16+newButton->gameObjectRect.h;

    newButton = new Button(0,0);
    newButton->setTexture(gameImages[HARD_BUTTON],gameRenderer);
    newButton->gameObjectRect.x = SCREEN_WIDTH/2 - newButton->gameObjectRect.w/2;
    newButton->gameObjectRect.y = SCREEN_HEIGHT/2+prevButtonHeight+16;
    diffMenu.addButton(newButton,HARD_PICKED);
}

void GameController::drawMainMenu()
{
    SDL_RenderClear(gameRenderer);
    mainMenu.drawMenu(gameRenderer);
    SDL_RenderPresent(gameRenderer);
}

void GameController::drawPauseMenu()
{
    SDL_RenderClear(gameRenderer);
    pauseMenu.drawMenu(gameRenderer);
    SDL_RenderPresent(gameRenderer);
}

void GameController::drawDiffMenu()
{
    SDL_RenderClear(gameRenderer);
    diffMenu.drawMenu(gameRenderer);
    SDL_RenderPresent(gameRenderer);
}

void GameController::drawP1Splash()
{
    SDL_RenderClear(gameRenderer);
    P1splash.drawMenu(gameRenderer);
    SDL_RenderPresent(gameRenderer);
}

void GameController::drawP2Splash()
{
    SDL_RenderClear(gameRenderer);
    P2splash.drawMenu(gameRenderer);
    SDL_RenderPresent(gameRenderer);
}

buttonEvent GameController::runMainMenu()
{
    buttonEvent currentEvent = NONE;

    SDL_Event menuTemp;

    while(currentEvent == NONE)
    {
        //Clear the event queue so SDL doesn't barf
        while(SDL_PollEvent(&menuTemp) != 0)
        {
            if(menuTemp.type == SDL_QUIT)
            {
                return QUIT;
            }
            else if(menuTemp.type == SDL_KEYDOWN)
            {
                if(menuTemp.key.keysym.sym == SDLK_ESCAPE)
                {
                    return QUIT;
                }
            }
            else if(menuTemp.type == SDL_MOUSEBUTTONDOWN)
            {
                currentEvent = mainMenu.mouseCheck();
            }
        }

        drawMainMenu();
    }

    return currentEvent;
}

buttonEvent GameController::runPauseMenu()
{
    buttonEvent currentEvent = NONE;

    SDL_Event menuTemp;

    while(currentEvent == NONE)
    {
        //Clear the event queue so SDL doesn't barf
        while(SDL_PollEvent(&menuTemp) != 0)
        {
            if(menuTemp.type == SDL_QUIT)
            {
                return QUIT;
            }
            else if(menuTemp.type == SDL_KEYDOWN)
            {
                if(menuTemp.key.keysym.sym == SDLK_ESCAPE)
                {
                    return QUIT;
                }
            }
            else if(menuTemp.type == SDL_MOUSEBUTTONDOWN)
            {
                currentEvent = pauseMenu.mouseCheck();
            }
        }

        drawPauseMenu();
    }

    return currentEvent;
}

buttonEvent GameController::runDiffMenu()
{
    buttonEvent currentEvent = NONE;

    SDL_Event menuTemp;

    while(currentEvent == NONE)
    {
        //Clear the event queue so SDL doesn't barf
        while(SDL_PollEvent(&menuTemp) != 0)
        {
            if(menuTemp.type == SDL_QUIT)
            {
                return QUIT;
            }
            else if(menuTemp.type == SDL_KEYDOWN)
            {
                if(menuTemp.key.keysym.sym == SDLK_ESCAPE)
                {
                    return QUIT;
                }
            }
            else if(menuTemp.type == SDL_MOUSEBUTTONDOWN)
            {
                currentEvent = diffMenu.mouseCheck();
            }
        }

        drawDiffMenu();
    }

    return currentEvent;
}

buttonEvent GameController::runP1Splash()
{
    buttonEvent currentEvent = NONE;

    SDL_Event menuTemp;

    while(currentEvent == NONE)
    {
        //Clear the event queue so SDL doesn't barf
        while(SDL_PollEvent(&menuTemp) != 0)
        {
            if(menuTemp.type == SDL_QUIT)
            {
                return QUIT;
            }
            else if(menuTemp.type == SDL_KEYDOWN)
            {
                if(menuTemp.key.keysym.sym == SDLK_ESCAPE)
                {
                    return QUIT;
                }
            }
            else if(menuTemp.type == SDL_MOUSEBUTTONDOWN)
            {
                currentEvent = P1splash.mouseCheck();
            }
        }

        drawP1Splash();
    }

    return currentEvent;
}

buttonEvent GameController::runP2Splash()
{
    buttonEvent currentEvent = NONE;

    SDL_Event menuTemp;

    while(currentEvent == NONE)
    {
        //Clear the event queue so SDL doesn't barf
        while(SDL_PollEvent(&menuTemp) != 0)
        {
            if(menuTemp.type == SDL_QUIT)
            {
                return QUIT;
            }
            else if(menuTemp.type == SDL_KEYDOWN)
            {
                if(menuTemp.key.keysym.sym == SDLK_ESCAPE)
                {
                    return QUIT;
                }
            }
            else if(menuTemp.type == SDL_MOUSEBUTTONDOWN)
            {
                currentEvent = P2splash.mouseCheck();
            }
        }

        drawP2Splash();
    }

    return currentEvent;
}

SDL_Surface* GameController::loadSurface(std::string path)
{
    SDL_Surface *loadSurface;
    loadSurface = IMG_Load(path.c_str());

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

    gameImages[SINGLE_BUTTON] = loadSurface("images/singleplayer.png");
    if(gameImages[SINGLE_BUTTON] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[MULTI_BUTTON] = loadSurface("images/multiplayer.png");
    if(gameImages[MULTI_BUTTON] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[MAIN_MENU_BUTTON] = loadSurface("images/mainmenu.png");
    if(gameImages[MAIN_MENU_BUTTON] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[RESUME_BUTTON] = loadSurface("images/resume.png");
    if(gameImages[RESUME_BUTTON] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[EASY_BUTTON] = loadSurface("images/easybutton.png");
    if(gameImages[EASY_BUTTON] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[MEDIUM_BUTTON] = loadSurface("images/medium.png");
    if(gameImages[MEDIUM_BUTTON] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[HARD_BUTTON] = loadSurface("images/hard.png");
    if(gameImages[HARD_BUTTON] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[P1_WIN_SPLASH] = loadSurface("images/p1winsplash.png");
    if(gameImages[P1_WIN_SPLASH] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[P2_WIN_SPLASH] = loadSurface("images/p2winsplash.png");
    if(gameImages[P2_WIN_SPLASH] == NULL){
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

    gameImages[BALL] = loadSurface("images/ball.png");
    if(gameImages[BALL] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    gameImages[VELOCITY_POWER] = loadSurface("images/blue_shell.png");
    if(gameImages[VELOCITY_POWER] == NULL){
        cout << "FAILED TO LOAD IMAGE" << endl;
        return false;
    }

    return success;
}

void GameController::setupObjects(){


    Button *newButton = new Button(0,0);
    newButton->setTexture(gameImages[P1_WIN_SPLASH],gameRenderer);
    P1splash.addButton(newButton,MAIN_MENU);

    newButton = new Button(0,0);
    newButton->setTexture(gameImages[P2_WIN_SPLASH],gameRenderer);
    P2splash.addButton(newButton,MAIN_MENU);

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
    ball.resetBall();

    powerUpList.resize(TOTAL_POWER_UPS);
    randomPowerUp = 0;

    powerUpList[TEST_ITEM].setTexture(gameImages[VELOCITY_POWER], gameRenderer);
}

void GameController::runGame()
{
    playerOne.setScore(0,gameImages[NUMBER_ZERO],gameRenderer);
    playerTwo.setScore(0,gameImages[NUMBER_ZERO],gameRenderer);
    buttonEvent menuEvent = runMainMenu();
    cout << "Done with menu." << endl;

    if(menuEvent == START_PVP)
    {
        startMultiplayer();
    }
    else if(menuEvent == START_AI)
    {
        menuEvent = runDiffMenu();
        if(menuEvent == EASY_PICKED)
        {
            AISpeedCap = 3;
        }
        else if(menuEvent == MEDIUM_PICKED)
        {
            AISpeedCap = 6;
        }
        else
        {
            AISpeedCap = 9;
        }
        startSingleplayer();
    }
}

void GameController::applyTexture(GameObject& updatedObject)
{
    if(debugMode)
    {
        SDL_Rect drawRect = updatedObject.gameObjectRect;
        SDL_SetRenderDrawColor(gameRenderer,0xFF,0x00,0x00,0xFF);
        SDL_RenderDrawLine(gameRenderer,drawRect.x,drawRect.y,drawRect.x+drawRect.w,drawRect.y); //top line
        SDL_RenderDrawLine(gameRenderer,drawRect.x,drawRect.y,drawRect.x,drawRect.y+drawRect.h); //left line
        SDL_RenderDrawLine(gameRenderer,drawRect.x+drawRect.w,drawRect.y,drawRect.x+drawRect.w,drawRect.y+drawRect.h); //right line
        SDL_RenderDrawLine(gameRenderer,drawRect.x,drawRect.y+drawRect.h,drawRect.x+drawRect.w,drawRect.y+drawRect.h); //bottom line
    }
    else
    {
        SDL_RenderCopy(gameRenderer,updatedObject.getTexture(),NULL,&updatedObject.gameObjectRect);
    }
}

void GameController::startMultiplayer()
{
    buttonEvent pauseEvent = NONE;
    while(quit == false)
    {
        //Input from players

        SDL_RenderClear(gameRenderer);

        //First player actions
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_KEYDOWN)
            {
                if( e.key.keysym.sym  == SDLK_w)
                {
                    playerOne.setUpPressed(true);

                }

                if( e.key.keysym.sym  == SDLK_s)
                {
                    playerOne.setDownPressed(true);
                }
            }
            else if(e.type == SDL_KEYUP)
            {
                if( e.key.keysym.sym  == SDLK_w)
                {
                    playerOne.setUpPressed(false);
                }

                if( e.key.keysym.sym  == SDLK_s)
                {
                    playerOne.setDownPressed(false);
                }
            }

            //Second player actions
            if( e.type == SDL_KEYDOWN)
            {
                if( e.key.keysym.sym  == SDLK_UP)
                {
                    playerTwo.setUpPressed(true);
                }

                if( e.key.keysym.sym  == SDLK_DOWN)
                {
                    playerTwo.setDownPressed(true);
                }
            }
            else if(e.type == SDL_KEYUP)
            {
                if( e.key.keysym.sym  == SDLK_UP)
                {
                    playerTwo.setUpPressed(false);
                }

                if( e.key.keysym.sym  == SDLK_DOWN)
                {
                    playerTwo.setDownPressed(false);
                }
            }

            //General gamestate actions
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym  == SDLK_ESCAPE)
                {
                    quit = true;
                }

                if(e.key.keysym.sym  == SDLK_LSHIFT|| e.key.keysym.sym == SDLK_RSHIFT)
                {
                   debugMode = !debugMode;
                }

                if(e.key.keysym.sym  == SDLK_LCTRL || e.key.keysym.sym == SDLK_RCTRL)
                {
                   seizureMode = !seizureMode;
                   if(!seizureMode)
                   {
                       SDL_SetRenderDrawColor(gameRenderer,0x00,0x00,0x00,0xFF);
                   }
                }

                if(e.key.keysym.sym == SDLK_p)
                {
                    pauseEvent = runPauseMenu();
                    if(pauseEvent != RESUME)
                    {
                        quit = true;
                        break;
                    }
                }
            }
            else if(e.type == SDL_QUIT)
            {
                quit = true;
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

        int mouseX,mouseY;
        SDL_GetMouseState(&mouseX,&mouseY);

        int scoreSide = moveBall();

        if(scoreSide == 1)
        {
            playerScored(playerTwo);
            ball.resetBall();
        }
        else if(scoreSide == 2)
        {
            playerScored(playerOne);
            ball.resetBall();
        }

        if(playerOne.getScoreValue() == 10 || playerTwo.getScoreValue() == 10)
        {
            quit = true;
            break;
        }

        if(seizureMode)
        {
            SDL_SetRenderDrawColor(gameRenderer,rand() % 0xFF,rand() % 0xFF, rand() % 0xFF, rand() % 0xFF);
        }



        displayObjects();




        place_meeting(mouseX,mouseY,&playerOne,&playerTwo);
        collision_line(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,mouseX,mouseY,&playerTwo);

        SDL_RenderPresent(gameRenderer);
    }

    if(playerOne.getScoreValue() == 10)
    {
        pauseEvent = runP1Splash();
    }
    else if(playerTwo.getScoreValue() == 10)
    {
        pauseEvent = runP2Splash();
    }

    if(pauseEvent == MAIN_MENU)
    {
        quit = false;
        runGame();
    }
}

void GameController::startSingleplayer()
{
    buttonEvent pauseEvent = NONE;
    while(quit == false)
    {
        //Input from player

        //First player actions
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_KEYDOWN)
            {
                if( e.key.keysym.sym  == SDLK_w)
                {
                    playerOne.setUpPressed(true);
                }

                if( e.key.keysym.sym  == SDLK_s)
                {
                    playerOne.setDownPressed(true);
                }
            }
            else if(e.type == SDL_KEYUP)
            {
                if( e.key.keysym.sym  == SDLK_w)
                {
                    playerOne.setUpPressed(false);
                }

                if( e.key.keysym.sym  == SDLK_s)
                {
                    playerOne.setDownPressed(false);
                }
            }

            //General gamestate actions
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym  == SDLK_ESCAPE)
                {
                    quit = true;
                }

                if(e.key.keysym.sym  == SDLK_LSHIFT|| e.key.keysym.sym == SDLK_RSHIFT)
                {
                   debugMode = !debugMode;
                }

                if(e.key.keysym.sym  == SDLK_LCTRL || e.key.keysym.sym == SDLK_RCTRL)
                {
                   seizureMode = !seizureMode;
                   if(!seizureMode)
                   {
                       SDL_SetRenderDrawColor(gameRenderer,0x00,0x00,0x00,0xFF);
                   }
                }

                if(e.key.keysym.sym == SDLK_p)
                {
                    pauseEvent = runPauseMenu();
                    if(pauseEvent != RESUME)
                    {
                        quit = true;
                        break;
                    }
                }
            }
            else if(e.type == SDL_QUIT)
            {
                quit = true;
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

        if(point_distance(0,playerTwo.gameObjectRect.y+playerTwo.gameObjectRect.h/2,
                          0,ball.gameObjectRect.y+ball.gameObjectRect.h/2) >= AISpeedCap)
        {
            if(playerTwo.gameObjectRect.y+playerTwo.gameObjectRect.h/2 < ball.gameObjectRect.y+ball.gameObjectRect.h/2)
            {
                playerTwo.gameObjectRect.y += AISpeedCap;
            }
            else
            {
                playerTwo.gameObjectRect.y -= AISpeedCap;
            }
        }
        else
        {
            playerTwo.gameObjectRect.y = ball.gameObjectRect.y+ball.gameObjectRect.h/2-playerTwo.gameObjectRect.h/2;
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

        int mouseX,mouseY;
        SDL_GetMouseState(&mouseX,&mouseY);

        int scoreSide = moveBall();

        if(scoreSide == 1)
        {
            playerScored(playerTwo);
            ball.resetBall();
        }
        else if(scoreSide == 2)
        {
            playerScored(playerOne);
            ball.resetBall();
        }

        SDL_RenderClear(gameRenderer);

        if(seizureMode)
        {
            SDL_SetRenderDrawColor(gameRenderer,rand() % 0xFF,rand() % 0xFF, rand() % 0xFF, rand() % 0xFF);
        }

        displayObjects();

        place_meeting(mouseX,mouseY,&playerOne,&playerTwo);
        collision_line(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,mouseX,mouseY,&playerTwo);

        SDL_RenderPresent(gameRenderer);
    }

    if(pauseEvent == MAIN_MENU)
    {
        quit = false;
        runGame();
    }
}

int GameController::moveBall()
{
    //chance to spawn power-ups as ball moves

    float newBallX,newBallY;

    newBallX = ball.xPosition + ball.getXVelocity();
    newBallY = ball.yPosition + ball.getYVelocity();

    if(newBallY < 0 || newBallY > SCREEN_HEIGHT-(ball.gameObjectRect.h))
    {
        ball.verticalBounce();
        if(newBallY < 0)
        {
            newBallY = 0;
        }
        else
        {
            newBallY = SCREEN_HEIGHT-(ball.gameObjectRect.h);
        }
    }

    if(place_meeting(newBallX,newBallY,&ball,&playerOne))
    {
        ballHitBy = PLAYER_ONE;
        ball.horizontalBounce();
        newBallX = ball.gameObjectRect.x;
        spawnRandomPowerUps();
    }
    else if(place_meeting(newBallX,newBallY,&ball,&playerTwo))
    {
        ballHitBy = PLAYER_TWO;
        ball.horizontalBounce();
        newBallX = ball.gameObjectRect.x;
        spawnRandomPowerUps();
    }

    if(newBallX <= playerOne.gameObjectRect.x+playerOne.gameObjectRect.w)
    {
        return 1;
    }
    else if(newBallX >= playerTwo.gameObjectRect.x-ball.gameObjectRect.w)
    {
        return 2;
    }

    checkPowerUps(newBallX, newBallY);

    ball.xPosition = newBallX;
    ball.yPosition = newBallY;
    ball.gameObjectRect.x = ball.xPosition;
    ball.gameObjectRect.y = ball.yPosition;

    return 0;
}

bool GameController::place_meeting(int checkX, int checkY, GameObject *startObject, GameObject *checkObject)
{
    SDL_Rect startRect = startObject->gameObjectRect;

    bool leftCol = collision_line(checkX,checkY,checkX,checkY+startRect.h,checkObject);
    bool topCol = collision_line(checkX,checkY,checkX+startRect.w,checkY,checkObject);
    bool rightCol = collision_line(checkX+startRect.w,checkY,checkX+startRect.w,checkY+startRect.h,checkObject);
    bool bottomCol = collision_line(checkX,checkY+startRect.h,checkX+startRect.w,checkY+startRect.h,checkObject);

    if( topCol || leftCol || rightCol || bottomCol)
    {
        return true;
    }

    return false;
}

bool GameController::collision_line(int startX, int startY, int endX, int endY, GameObject *checkObject)
{
    double checkAngle = atan2(endX-startX,endY-startY);
    int checkDistance = point_distance(startX,startY,endX,endY);

    bool collided = false;
    int checkX, checkY;
    for(int i = 0; i <= checkDistance; i++)
    {
        checkX = startX+i*sin(checkAngle);
        checkY = startY+i*cos(checkAngle);

        if(collision_point(checkX,checkY,checkObject))
        {
            collided = true;
        }
    }

    //draw debug line
    if(debugMode)
    {
        if(collided)
        {
            SDL_SetRenderDrawColor(gameRenderer,0x00,0xFF,0x00,0xFF);
        }
        else
        {
            SDL_SetRenderDrawColor(gameRenderer,0xFF,0x00,0x00,0xFF);
        }

        for(int i = 0; i <= checkDistance; i++)
        {
            checkX = startX+i*sin(checkAngle);
            checkY = startY+i*cos(checkAngle);

            SDL_RenderDrawPoint(gameRenderer,checkX,checkY);
        }

        SDL_SetRenderDrawColor(gameRenderer,0x00,0x00,0x00,0xFF);
    }

    return collided;
}

bool GameController::collision_point(int checkX, int checkY, GameObject *checkObject)
{
    SDL_Rect checkRect = checkObject->gameObjectRect;

    if(checkX >= checkRect.x && checkX <= checkRect.x + checkRect.w && checkY >= checkRect.y && checkY <= checkRect.y + checkRect.h)
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

void GameController::playerScored(Player& scoringPlayer){

    int tempScore = scoringPlayer.getScoreValue();
    tempScore++;

    switch(tempScore){
    case 1:
        scoringPlayer.setScore(tempScore, gameImages[NUMBER_ONE], gameRenderer);
        break;
    case 2:
        scoringPlayer.setScore(tempScore, gameImages[NUMBER_TWO], gameRenderer);
        break;
    case 3:
        scoringPlayer.setScore(tempScore, gameImages[NUMBER_THREE], gameRenderer);
        break;
    case 4:
        scoringPlayer.setScore(tempScore, gameImages[NUMBER_FOUR], gameRenderer);
        break;
    case 5:
        scoringPlayer.setScore(tempScore, gameImages[NUMBER_FIVE], gameRenderer);
        break;
    case 6:
        scoringPlayer.setScore(tempScore, gameImages[NUMBER_SIX], gameRenderer);
        break;
    case 7:
        scoringPlayer.setScore(tempScore, gameImages[NUMBER_SEVEN], gameRenderer);
        break;
    case 8:
        scoringPlayer.setScore(tempScore, gameImages[NUMBER_EIGHT], gameRenderer);
        break;
    case 9:
        scoringPlayer.setScore(tempScore, gameImages[NUMBER_NINE], gameRenderer);
        break;
    case 10:
        scoringPlayer.setScore(tempScore, gameImages[NUMBER_NINE], gameRenderer);

        //You win
        break;
    }
}


void GameController::spawnRandomPowerUps()
{
    bool oneIsSpawned = false;

    for(int i = 0; i < TOTAL_POWER_UPS; i++)
    {
        if(powerUpList[i].getIsOnScreen() == true)
        {
            oneIsSpawned = true;
        }
    }

    if(oneIsSpawned == false)
    {
        randomPowerUp =  rand() % (30 * POWER_UP_RATE +1);
        if(randomPowerUp <= 40)
        {
            randomPowerUp = rand() % TOTAL_POWER_UPS;
            if(powerUpList[randomPowerUp].getTexture() != false)
            {
                powerUpList[randomPowerUp].spawnPowerUp(10);
            }
        }
    }
}

void GameController::displayObjects()
{
        applyTexture(playerOne);
        applyTexture(playerTwo);
        applyTexture(playerOne.getMyScore());
        applyTexture(playerTwo.getMyScore());
        applyTexture(ball);

    for (int i = 0; i < TOTAL_POWER_UPS; i++)
    {
        if(powerUpList[i].getIsOnScreen())
        {
            applyTexture(powerUpList[TEST_ITEM]);
        }
    }
}

void GameController::checkPowerUps(int newBallX, int newBallY)
{
    for(int i = 0; i < TOTAL_POWER_UPS; i++)
    {
        if(powerUpList[i].getIsOnScreen())
        {
            if(place_meeting(newBallX,newBallY,&ball,&powerUpList[i]))
            {
                if(ballHitBy == PLAYER_ONE)
                {
                    playerOne.pickedUp(powerUpList[i]);
                }
                else if (ballHitBy == PLAYER_TWO)
                {
                    playerTwo.pickedUp(powerUpList[i]);
                }
            }
        }
    }
}
