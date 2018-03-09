//
//  ChessGameUtils.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 09/03/2018.
//  Copyright © 2018 Daniel Meltzer. All rights reserved.
//

#include "ChessGameUtils.h"

bool verify_valid_start_pos_move(ChessGame* game, Cell* cell) {
    if (game->board->boardData[cell->row][cell->column] == NULL) return false;
    if (game->currentPlayerWhite != game->board->boardData[cell->row][cell->column]->isWhite) return false;
    return true;
}

bool verify_valid_end_pos_move(ChessGame* game, Cell* startCell, Cell* destCell) {
    if (game->board->boardData[destCell->row][destCell->column] == NULL) return true;
    // TODO: add checks, e.g. move is in get_possible_moves
    // TODO: also check can be eaten.
    return true;
}

/**
 Preforms a move, updates the UI/Console if needed.
 */
void preform_chess_game_move(ChessGame*game, Cell* startCell, Cell* destCell) {
    // TODO: remember if eats to free piece.
    preform_board_move(game->board, startCell, destCell);
    if (game->settings->guiMode == GAME_MODE_WITH_GUI) {
        draw_chess_board_according_to_state(game->board, game->boardWindow);
    }
    // TODO: CHECK FOR CHECK, CHECK-MATE ETC... REMEMBER TO SHOW A TEXTURE WITH THE RIGHT TEXT.
    
    game->currentPlayerWhite = !game->currentPlayerWhite;
}
