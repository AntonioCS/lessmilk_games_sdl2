/* 
 * File:   GameEngine_FSM.h
 * Author: antoniocs
 *
 * Created on 30 de Agosto de 2015, 21:20
 */

#ifndef GAMEENGINE_FSM_H
#define	GAMEENGINE_FSM_H

#include "GameEngine.h"

#ifdef	__cplusplus
extern "C" {
#endif

struct GameEngine_FSM_State;

typedef void GameEngine_FSM_State_FuncPtr(struct GameEngine_FSM_State *);

struct GameEngine_FSM_State  {
    GameEngine_FSM_State_FuncPtr *next;
    struct GameEngine_GameData *gameData;   
};


struct GameEngine_FSM_State *GameEngine_FMI_Init(GameEngine_FSM_State_FuncPtr *, struct GameEngine_GameData *);


#ifdef	__cplusplus
}
#endif

#endif	/* GAMEENGINE_FSM_H */

