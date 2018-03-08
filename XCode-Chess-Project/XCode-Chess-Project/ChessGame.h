//
//  ChessGame.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#ifndef ChessGame_h
#define ChessGame_h

// GAME MODES:

// GUI MODES:
#define GAME_MODE_CONSOLE 2
// GAME MODES:
#define GAME_MODE_AI 3
#define GAME_MODE_2_PLAYERS 4
#define MAX_LINE_LENGTH 3000
// DIFF STRINGS:

#define AMATEUR_STRING "amateur";
#define EASY_STRING "easy";
#define MODERATE_STRING "moderate";
//TODO:CHANGE!!!! TO hard
#define HARD_STRING "hard(;";
#define EXPERT_STRING "expert";

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "GUIChessWindow.h"
#include "LineParser.h"

typedef enum {
    GameFinishedActionMainMenu,
    GameFinishedActionQuit,
    GameFinishedActionReset,
} GameFinishedStatusEnum;

typedef struct _game_settings {
    int guiMode; // options: GAME_MODE_WITH_GUI, GAME_MODE_CONSOLE
    int gameMode; // options: GAME_MODE_AI, GAME_MODE_2_PLAYERS
    int difficulty; // options: 1-5
    int userColor; // options: BLACKCOLOR, WHITECOLOR;
} GameSettings;

typedef struct _chess_game {
    ChessBoard* board;
    GuiChessWindow* boardWindow; // This pointer will be null for console mode games
    GameSettings* settings;
    
} ChessGame;



GameSettings* get_game_settings(void);
ChessGame* init_game(GameSettings* settings);
void free_game(ChessGame* game);
void handle_sdl_event(ChessGame* game, SDL_Event* event);
GameFinishedStatusEnum* play_chess_game(ChessGame* game);

#endif /* ChessGame_h */
