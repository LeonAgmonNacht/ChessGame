//
//  ChessGameUtils.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 09/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#include "ChessGameUtils.h"
#include "MinimaxAI.h"
/**
 Returns if the game is in match, tie, check states
 */
GameFinishedStatusEnum get_game_status(ChessGame* game) {
    if (is_match(game->board, game->currentPlayerWhite)) return GameFinishedActionMate;
    if (is_tie(game->board, game->currentPlayerWhite)) return GameFinishedActionDraw;
    if (is_check(game->board, game->currentPlayerWhite)) return GameFinishedActionCheck;
    return GameFinishedActionUndetermined;
}

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
    List* moves = get_posibble_moves(startCell, game->board);
    bool validMove = false;
    for (int i = 0; i<get_items_count(moves); i++) {
        Move* move = (Move*)get_element(moves, i);
        if (are_cells_equal(&(move->cell), destCell)) {
            validMove = true;
        }
    }
    free_list(moves);
    return validMove;
}

/**
 Preforms a move, updates the UI/Console if needed.
 */
void preform_chess_game_move(ChessGame*game, Cell* startCell, Cell* destCell) {
    make_move_on_board(game->board, game->board->boardData[startCell->row][startCell->column] , destCell);
    //preform_board_move(game->board, startCell, destCell);
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
    DetailedMove* move = get_best_move(game->board, game->currentPlayerWhite, game->settings->difficulty);
    preform_chess_game_move(game, &move->fromCell, &move->move.cell);
    return ;
}
