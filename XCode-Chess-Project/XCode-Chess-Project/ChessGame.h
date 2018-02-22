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

#define GAME_MODE_WITH_GUI 0
#define GAME_MODE_CONSOLE 1

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "GUIChessWindow.h"

typedef struct _chess_game {
    chessBoard* board;
    guiChessWindow* boardWindow; // This pointer will be null for console mode games
} chessGame;

chessGame* init_game(int mode);

#endif /* ChessGame_h */
