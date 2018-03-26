//
//  ChessGameUtils.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 09/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#ifndef ChessGameUtils_h
#define ChessGameUtils_h
#include <stdlib.h>
#include <stdio.h>
#include "ChessGame.h"

/**
 Returns true iff the given cell represents a game piece that the current player can move.
 */
bool verify_valid_start_pos_move(ChessGame* game, Cell* cell);
/**
 Returns true iff the given start and end cells represents a valid move.
 */
bool verify_valid_end_pos_move(ChessGame* game, Cell* startCell, Cell* destCell);
/**
 Preforms a move, updates the UI/Console if needed.
 */
void preform_chess_game_move(ChessGame*game, Cell* startCell, Cell* destCell);
/**
 Types of result of undo command.
 */
typedef enum {
    UndoSuccess,
    UndoNoHistory,
} UndoMoveCallReturnType;

/**
 Undo a move in the given game if possible, returns the action status.
 */
UndoMoveCallReturnType undo_game_move(ChessGame* game);
/**
 Preforms a computer move
 */
void preform_computer_move(ChessGame* game);
/**
 Returns if the game is in match, tie, check states
 */
GameFinishedStatusEnum get_game_status(ChessGame* game);
#endif /* ChessGameUtils_h */
