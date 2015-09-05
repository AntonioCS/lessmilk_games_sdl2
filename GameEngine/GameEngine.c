
#include "GameEngine.h"
#include "dbg.h"
#include "Util/HexToRGB.h"

//static bool Init_SubSystems(struct GameEngine_SDL_SubSystems *);

#define DEFAULT_BACKGROUND_ALPHA 255

/**
 * Start everything here
 * 
 * @param options
 * @return
 */
struct GameEngine_GameData *GameEngine_Init_Base(struct GameEngine_InitOptions *options) {

    struct GameEngine_GameData *gameData = malloc(sizeof (struct GameEngine_GameData));
    check_mem(gameData);

    gameData->InitOptions = options;

    check(SDL_Init(options->SDLInitFlags) == 0, "Unable to initiate SDL:  %s\n", SDL_GetError());

    gameData->Window = SDL_CreateWindow(
            options->WindowOptions_Title,
            options->WindowOptions_Coords_x,
            options->WindowOptions_Coords_y,
            options->WindowOptions_Size_w,
            options->WindowOptions_Size_h,
            options->WindowOptions_Flags
            );
    check(gameData->Window, "Unable to create window: %s", SDL_GetError());

    gameData->Renderer = SDL_CreateRenderer(gameData->Window, options->RendererOptions_Index, options->RendererOptions_Flags);
    check(gameData->Renderer, "Unable to create renderer: %s", SDL_GetError());

    /*
    if (options->SubSys) {
        check(Init_SubSystems((options->SubSys)), "Failed to init sub system");
    }
    */
    
    gameData->BackGroundColour = NULL;
    gameData->BackGroundColourAlpha = DEFAULT_BACKGROUND_ALPHA;

    return gameData;

error:
    GameEngine_Quit(gameData);

    return NULL;
}

/**
 * Take care of initializing SDL Sub Systems (just IMG for now)
 * @param options
 * @return
 */
/*
bool Init_SubSystems(struct GameEngine_SDL_SubSystems *options) {

    if (options->IMG) {
        check(IMG_Init(options->IMG->Flags) & options->IMG->Flags, "Failed to initialize IMG: %s\n", SDL_GetError());
    }

    return true;

error:

    return false;
}
*/
/**
 * Take care of the final clean up
 * 
 * @param returnValues
 */
void GameEngine_Quit(struct GameEngine_GameData *gameData) {
    if (gameData) {
        if (gameData->Window) {
            if (gameData->Renderer) {
                SDL_DestroyRenderer(gameData->Renderer);
                gameData->Renderer = NULL;
            }

            SDL_DestroyWindow(gameData->Window);
            gameData->Window = NULL;
        }

        //Quit SDL subsystems
       // if (gameData->InitOptions->SubSys) {
         //   IMG_Quit();
       // }

        if (gameData->BackGroundColour) {
            free(gameData->BackGroundColour);
            gameData->BackGroundColour = NULL;
        }

        free(gameData);
        gameData = NULL;
    }

    SDL_Quit();
}

bool GameEngine_IsRunning(struct GameEngine_GameData *gameData) {
    return gameData->IsRunning;
}

void GameEngine_HandleEvents(struct GameEngine_GameData *gameData) {
    static SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {

        //User requests quit ----------- Quit also with ESCAPE key pressed
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
            gameData->IsRunning = false;
        }
        /*
       if (e.type == SDL_KEYDOWN) {
           switch (e.key.keysym.sym) {
               case SDLK_UP:
               case SDLK_w:
                   player_sprite.y = 48;
                   player_pos.y -= moveSpeed * deltaTime;
                   break;

               case SDLK_DOWN:
               case SDLK_s:
                   player_sprite.y = 0;
                   player_pos.y += moveSpeed * deltaTime;
                   break;

               case SDLK_LEFT:
               case SDLK_a:
                   player_sprite.y = 72;
                   player_pos.x -= moveSpeed * deltaTime;
                   break;

               case SDLK_RIGHT:
               case SDLK_d:
                   player_sprite.y = 24;
                   player_pos.x += moveSpeed * deltaTime;
                   break;

               case SDLK_SPACE:

                   break;
           }
       }
         * */
    }
}

void GameEngine_Render(struct GameEngine_GameData *gameData) {
    if (gameData->BackGroundColour) {
        GameEngine_ApplyBackGroundColour(gameData);
    } else {
        SDL_RenderClear(gameData->Renderer);
    }

    SDL_RenderPresent(gameData->Renderer);
}


bool GameEngine_SetBackGroundColour(struct GameEngine_GameData *gameData, const char *hexColour) {
    int i = 0;
    char buffer[SETBACKGROUNDCOLOUR_BUFFER_SIZE] = {0};

    if (gameData->BackGroundColour == NULL) {
        gameData->BackGroundColour = malloc(sizeof (struct GameEngine_RGB));
    }
    check(gameData->BackGroundColour, "Unable to allocate memory for RGB struct");

    if (hexColour[i] == '#') {
        i++;
    }
    check(strlen(hexColour + i) >= 6, "Wrong hex string. Must be at least 6 characters");

    for (; i <= 6; i += 2) {
        strncpy(buffer, hexColour + i, 2);
        int decimalValue = GameEngine_Util_ConvertHexStringToDec(buffer);
        check(decimalValue != -1, "Error converting %s to hex", buffer);

        if (i <= 1) {
            gameData->BackGroundColour->r = decimalValue;
        } else if (i <= 3) {
            gameData->BackGroundColour->g = decimalValue;
        } else {
            gameData->BackGroundColour->b = decimalValue;
        }

        memset(buffer, 0, SETBACKGROUNDCOLOUR_BUFFER_SIZE);
    }

    //printf("HEX: %s RGB: %d, %d, %d\n", hexColour, gameData->BackGroundColour->r, gameData->BackGroundColour->g, gameData->BackGroundColour->b);
    return GameEngine_ApplyBackGroundColour(gameData);

error:
    if (gameData->BackGroundColour != NULL) {
        free(gameData->BackGroundColour);
        gameData->BackGroundColour = NULL;
    }

    return false;
}

/**
 * Apply the Background colour set in gameData
 * @param gameData
 * @return
 */
bool GameEngine_ApplyBackGroundColour(struct GameEngine_GameData *gameData) {
    return (SDL_SetRenderDrawColor(gameData->Renderer, gameData->BackGroundColour->r, gameData->BackGroundColour->g, gameData->BackGroundColour->b, gameData->BackGroundColourAlpha) == 0 &&
            SDL_RenderClear(gameData->Renderer) == 0);
}