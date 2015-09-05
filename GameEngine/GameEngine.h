/* 
 * File:   GameEngine.h
 * Author: antoniocs
 *
 * Created on 30 de Agosto de 2015, 12:22
 */

#ifndef GAMEENGINE_H
#define	GAMEENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

    #define SETBACKGROUNDCOLOUR_BUFFER_SIZE 3

    struct GameEngine_RGB {
        Uint8 r;
        Uint8 g;
        Uint8 b;
    };   

    /*
    struct GameEngine_SDL_SubSystems {
        struct GameEngine_SDL_SubSystems_IMG_Options *IMG;
    };

    struct GameEngine_SDL_SubSystems_IMG_Options {
        int Flags; //https://www.libsdl.org/projects/SDL_image/docs/SDL_image_8.html
    };*/

    struct GameEngine_InitOptions {
        Uint32 SDLInitFlags; //https://wiki.libsdl.org/SDL_Init#Remarks

        const char *WindowOptions_Title;
        int WindowOptions_Coords_x;
        int WindowOptions_Coords_y;
        int WindowOptions_Size_w;
        int WindowOptions_Size_h;
        Uint32 WindowOptions_Flags; //https://wiki.libsdl.org/SDL_WindowFlags

        int RendererOptions_Index;
        Uint32 RendererOptions_Flags; //https://wiki.libsdl.org/SDL_RendererFlags

      
        //struct GameEngine_SDL_SubSystems *SubSys;
    };

    struct GameEngine_GameData {
        struct GameEngine_InitOptions *InitOptions;

        //The window renderer
        SDL_Renderer *Renderer;

        //The window we'll be rendering to
        SDL_Window *Window;

        bool IsRunning;

        struct GameEngine_RGB *BackGroundColour;
        int BackGroundColourAlpha;
    };

    struct GameEngine_GameData *GameEngine_Init_Base(struct GameEngine_InitOptions *);

    void GameEngine_Quit(struct GameEngine_GameData *);

    void GameEngine_HandleEvents(struct GameEngine_GameData *);
    void GameEngine_Update(struct GameEngine_GameData *);
    void GameEngine_Render(struct GameEngine_GameData *);
    bool GameEngine_IsRunning(struct GameEngine_GameData *);


    bool GameEngine_SetBackGroundColour(struct GameEngine_GameData *, const char *);
    bool GameEngine_SetAlpha(struct GameEngine_GameData *, const char *);

    bool GameEngine_ApplyBackGroundColour(struct GameEngine_GameData *);


#define GameEngine_Init(...) GameEngine_Init_Base(&( \
    (struct GameEngine_InitOptions){\
                                                        .SDLInitFlags = SDL_INIT_VIDEO,\
                                                        \
                                                        .WindowOptions_Title = "SDL Window",\
                                                        .WindowOptions_Coords_x = SDL_WINDOWPOS_CENTERED,\
                                                        .WindowOptions_Coords_y = SDL_WINDOWPOS_CENTERED,\
                                                        .WindowOptions_Size_w = 400,\
                                                        .WindowOptions_Size_h = 500,\
                                                        .WindowOptions_Flags = SDL_WINDOW_SHOWN,\
                                                        \
                                                        .RendererOptions_Index = 0,\
                                                        .RendererOptions_Flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC,\
                                                        __VA_ARGS__\
    }\
))

#ifdef	__cplusplus
}
#endif

#endif	/* GAMEENGINE_H */

