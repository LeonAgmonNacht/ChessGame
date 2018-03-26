//
//  ChessGameUtils.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 09/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#include "ChessGameUtils.h"

/**
 Returns true iff the given cell represents a game piece that the current player can move.
 */
bool verify_valid_start_pos_move(ChessGame* game, Cell* cell) {
    if (game->board->boardData[cell->row][cell->column] == NULL) return false;
    if (game->currentPlayerWhite != game->board->boardData[cell->row][cell->column]->isWhite) return false;
    return true;
}
/**
 Returns true iff the given start and end cells represents a valid move.
 */
bool verify_valid_end_pos_move(ChessGame* game, Cell* startCell, Cell* destCell) {
    if (game->board->boardData[destCell->row][destCell->column] == NULL) return true;
    // TODO: Meltzer add these once done.
    // TODO: add checks, e.g. move is in get_possible_moves
    // TODO: also check can be eaten.
    return true;
}

/**
 Preforms a move, updates the UI/Console if needed.
 */
void preform_chess_game_move(ChessGame*game, Cell* startCell, Cell* destCell) {
    preform_board_move(game->board, startCell, destCell);
    if (game->settings->guiMode == GAME_MODE_WITH_GUI) {
        draw_chess_board_according_to_state(game->board, game->boardWindow, NULL);
    }

    game->currentPlayerWhite = !game->currentPlayerWhite;
    game->saved = false;
}
/**
 Undo a move in the given game if possible, returns the action status.
 */
UndoMoveCallReturnType undo_game_move(ChessGame* game) {
    // TODO: Implement, dont forget to print if console and if game was undo
    return UndoNoHistory;
}

/**
 Preforms a computer move
 */
void preform_computer_move(ChessGame* game) {
    // TODO: meltzer implement, return what happend due to the computer move.
    return ;
}
