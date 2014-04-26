#include <SDL.h>
// #include <stdio.h>
#include "GameController.h"



void testDriver();

int main(int argc, char* args[]){
    testDriver();
    return 0;
}

void testDriver(){
    GameController pong;
    pong.testGame();
}
