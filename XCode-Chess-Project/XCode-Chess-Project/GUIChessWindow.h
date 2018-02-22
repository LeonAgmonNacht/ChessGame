//
//  GUIChessWindow.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#ifndef GUIChessWindow_h
#define GUIChessWindow_h

#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include "GamePieces.h"
#include "ChessBoard.h"
#define WIN_TITLE "Chess Game"
#define WIN_WIDTH 1024
#define WIN_HEIGHT 768
#define GAMEGUIBOARDSIZE 768
#define BOARD_SIZE 8
#define PIECE_SIZE GAMEGUIBOARDSIZE/BOARD_SIZE


typedef struct _gui_chess_window {
    SDL_Window *window;
    SDL_Renderer *window_renderer;
    
} guiChessWindow;

void draw_chess_board_according_to_state(chessBoard* board, guiChessWindow* window);

guiChessWindow* init_gui_window();

#endif /* GUIChessWindow_h */
