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

/**
 A struct holding the data for a gui chess window.
 */
typedef struct _gui_chess_window {
    SDL_Window *window;
    SDL_Renderer *windowRenderer;
    SDL_Texture* texturesForAllGameGraphicalPieces[PLAYERS_COUNT][NUMBER_OF_GAME_PIECE_TYPES];
} GuiChessWindow;

/**
 Enum for the actions that may occurr in the chess main screen
 */
typedef enum {
    RestartClicked,
    SaveClicked,
    LoadClicked,
    UndoClicked,
    MainMenuClicked,
    QuitClicked,
    BoardMove
    
} ChessWindowActionType;
/**
 A struct for an action in the mainmenu, basically ChessWindowActionType but holds data if the action is move.
 */
typedef struct ChessWindowAction {
    ChessWindowActionType actionType;
    Cell* cellClicked; // In case of a BoardMove action, this Cell will hold the row,col that was pressed
    bool isRightClick; // In case of a BoardMove action, this will be true iff the click was a click on the right mouse
} ChessWindowAction;
/**
 Mallocs and inits a new gui window.
 */
GuiChessWindow* init_gui_window(void);
/**
 Frees all resources used by the chess gui window, including SDL ones.
 */
void free_gui_window(GuiChessWindow* window);
/**
 Renders the data in the board on the given window including game pieces and buttons
 cellsColors is a list of CellColor, these cells will be colord in a costum color (as in their CellColor)
 */
void draw_chess_board_according_to_state(ChessBoard * board, GuiChessWindow * window, List* cellsColors);

/**
 Frees all resources.
 */
void free_window_action(ChessWindowAction* action);
/**
 Waits until a move has been made or a button was clicked.
 */
ChessWindowAction* wait_for_move_or_action(void);


#endif /* GUIChessWindow_h */
