/*
 * File:   main.c
 * Author: antoniocs
 *
 * Created on 16 de Julho de 2015, 21:46
 */

#include <SDL.h>
#include <SDL_image.h>
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

    float frameTime = 0;
    float deltaTime = 0; //change in time
    int prevTime = 0;
    int currentTime = 0;
    float moveSpeed = 400.0f;

    //const int FPS = 60;
    //const int DELAY_TIME = 1000.0f / FPS;


    //The window renderer
    SDL_Renderer *renderer = NULL;

    //The window we'll be rendering to
    SDL_Window *gWindow;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        //Create window
        gWindow = SDL_CreateWindow("LessMilk Game #1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow != NULL) {
            //Get window surface
            renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            int imgFlags = IMG_INIT_PNG;

            if (IMG_Init(imgFlags) & imgFlags) {
                bool isRunning = true;

                //Event handler
                SDL_Event e;

                SDL_Texture *player = IMG_LoadTexture(renderer, PLAYER_PIC);
                SDL_Texture *enemy1 = IMG_LoadTexture(renderer, ENEMY1_PIC);
                SDL_Texture *enemy2 = IMG_LoadTexture(renderer, ENEMY2_PIC);


                //SDL_Texture *texture = IMG_LoadTexture(renderer, PATH_TO_IMAGE);
                //int selected_frame = 0;
                int position_x = 0;
                SDL_Rect player_pos = {
                    .x = SCREEN_WIDTH / 2 - 10,
                    .y = SCREEN_HEIGHT / 2 - 12,
                    .w = 20,
                    .h = 24
                };

                SDL_Rect player_sprite = {
                    .x = 0,
                    .y = 0,
                    .w = 20,
                    .h = 24

                };

                while (isRunning) {
                    prevTime = currentTime;
                    currentTime = SDL_GetTicks();
                    deltaTime = (currentTime - prevTime) / 1000.0f;

                    //Handle events on queue
                    //IMPORTANT - Without this the program will crash
                    //we must always process all the events
                    ///*
                    while (SDL_PollEvent(&e) != 0) {
                        //User requests quit ----------- Quit also with ESCAPE key pressed
                        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                            isRunning = false;
                        }
///*
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
                    }

                    frameTime += deltaTime;
                    //*/
                    if (frameTime >= 0.10f) {
                        frameTime = 0;

                        if (player_sprite.x >= 20) {
                            player_sprite.x = 0;
                        }
                        else {
                            player_sprite.x += 20;
                        }

                    }

                    SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOUR, 0xFF);
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, player, &player_sprite, &player_pos);
                    SDL_RenderPresent(renderer);

                    //SDL_SetWindowTitle(gWindow);

                    printf("Deltatime: %f - %f\n", deltaTime, frameTime);

                    //printf("Selected frame: %d -- %d - %d\n", selected_frame, frame, WALKING_ANIMATION_FRAMES);

                }
            }


        } else {
            printf("SDL_Init failed ON WINDOW: %s\n", SDL_GetError());
        }
    }

    //Destroy window
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();


    return (EXIT_SUCCESS);
}

void printf_rect(SDL_Rect *rect) {
    printf("Rect X: %d, Y: %d, W: %d, H: %d\n", rect->x, rect->y, rect->w, rect->h);
}
