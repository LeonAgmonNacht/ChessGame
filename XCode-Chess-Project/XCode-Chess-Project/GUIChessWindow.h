//
//  GUIChessWindow.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#ifndef GUIChessWindow_h
#define GUIChessWindow_h

#include <stdio.h>

#include "GamePieces.h"
#include "ChessBoard.h"



typedef struct _gui_chess_window {
    SDL_Window *window;
    SDL_Renderer *window_renderer;
    SDL_Texture* TexturesForAllGameGraphicalPieces[PLAYERS_COUNT][NUMBER_OF_GAME_PIECES];
} GuiChessWindow;

void draw_chess_board_according_to_state(ChessBoard* board, GuiChessWindow* window);

GuiChessWindow* init_gui_window(void);

#endif /* GUIChessWindow_h */
