//
//  ChessBoard.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include "ChessBoard.h"

// TODO: Implement
void _init_board_data(chessBoard* board) {
    
}

chessBoard* init_game_board() {
    
    // MEM:
    
    chessBoard* board = (chessBoard *) malloc(sizeof(chessBoard));
    board->boardData = (char *) malloc(BOARD_SIZE * BOARD_SIZE);
    
    // INIT:
    
    // TODO: Init game pieces and then call init board, that will create the inital state of a chess board.
    _init_board_data(board);
    
    return board;
}
