//
//  ChessGame.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
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
#define HARD_STRING "hard";
#define EXPERT_STRING "expert";

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "GUIChessWindow.h"
#include "LineParser.h"

typedef struct _game_settings {
    int guiMode; // options: GAME_MODE_WITH_GUI, GAME_MODE_CONSOLE
    int gameMode; // options: GAME_MODE_AI, GAME_MODE_2_PLAYERS
    int difficulty; // options: 1-5
    int userColor; // options: BLACKCOLOR, WHITECOLOR;
} gameSettings;

typedef struct _chess_game {
    chessBoard* board;
    guiChessWindow* boardWindow; // This pointer will be null for console mode games
    gameSettings* settings;
} chessGame;



gameSettings* get_game_settings();
chessGame* init_game(gameSettings* settings);
void handle_sdl_event(chessGame* game, SDL_Event* event);
#endif /* ChessGame_h */
