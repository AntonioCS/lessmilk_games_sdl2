/* 
 * File:   main.c
 * Author: antoniocs
 *
 * Created on 16 de Julho de 2015, 21:46
 */

#include <SDL.h>
#include <SDL_image.h>
#include "../GameEngine/GameEngine.h"
#include "../GameEngine/GameEngine_FSM.h"
#include "../GameEngine/dbg.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//Screen dimension constants
const int SCREEN_WIDTH = 350;
const int SCREEN_HEIGHT = 350;

#define PLAYER_PIC "C:/Users/antoniocs/Projects/Personal/c/games/SDL2/lessmilkgames/game1/images/player.png" //20x24 sprite
#define ENEMY1_PIC "C:/Users/antoniocs/Projects/Personal/c/games/SDL2/lessmilkgames/game1/images/enemy1.png" //32x36 sprite
#define ENEMY2_PIC "C:/Users/antoniocs/Projects/Personal/c/games/SDL2/lessmilkgames/game1/images/enemy2.png" //28x40 sprite
#define BACKGROUND_COLOUR 52, 73, 94

int main(int argc, char* args[]) {

    int exit_state = EXIT_SUCCESS;

    struct GameEngine_GameData *gameData = GameEngine_Init();
    check(gameData, "Failure to initialize Game Engine");

    log_info("It worked.");

    GameEngine_SetBackGroundColour(gameData, "#34495E");

    while (GameEngine_IsRunning(gameData)) {
        GameEngine_HandleEvents(gameData);
        //GameEngine_Update(gameData);

        GameEngine_Render(gameData);
        //SDL_Delay(10);
    }


terminate:
    GameEngine_Quit(gameData);
    return (exit_state);

error:
    exit_state = EXIT_FAILURE;
    goto terminate;
}

