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
#include "ChessGamesLogic.h"
#include "GamePieces.h"
#include "ChessBoard.h"

typedef struct _gui_chess_window {
    SDL_Window *window;
    SDL_Renderer *windowRenderer;
    SDL_Texture* TexturesForAllGameGraphicalPieces[PLAYERS_COUNT][NUMBER_OF_GAME_PIECE_TYPES];
} GuiChessWindow;


typedef enum {
    RestartClicked,
    SaveClicked,
    LoadClicked,
    UndoClicked,
    MainMenuClicked,
    QuitClicked,
    BoardMove
    
} ChessWindowActionType;

typedef struct ChessWindowAction {
    ChessWindowActionType actionType;
    Cell* cellClicled; // In case of a BoardMove action, this Cell will hold the row,col that was pressed
} ChessWindowAction;

GuiChessWindow* init_gui_window(void);

void draw_chess_board_according_to_state(ChessBoard * board, GuiChessWindow * window);

//GameFinishedStatusEnum



#endif /* GUIChessWindow_h */
