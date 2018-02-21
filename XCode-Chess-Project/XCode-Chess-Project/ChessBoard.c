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
    
    // init pawns:
    for (int i = 0; i<BOARD_SIZE; i++) (board->boardData)[1][i] = board->pawnWhite->symbol;
    for (int i = 0; i<BOARD_SIZE; i++) (board->boardData)[6][i] = board->pawnBlack->symbol;
    
    // init others:
    (board->boardData)[0][0] = board->rookWhite->symbol;(board->boardData)[0][7] = board->rookWhite->symbol;
    (board->boardData)[0][1] = board->knightWhite->symbol;(board->boardData)[0][6] = board->knightWhite->symbol;
    (board->boardData)[0][2] = board->bishopWhite->symbol;(board->boardData)[0][5] = board->bishopWhite->symbol;
    (board->boardData)[0][3] = board->kingWhite->symbol;(board->boardData)[0][4] = board->queenWhite->symbol;
    
    (board->boardData)[7][0] = board->rookBlack->symbol;(board->boardData)[7][7] = board->rookBlack->symbol;
    (board->boardData)[7][1] = board->knightBlack->symbol;(board->boardData)[7][6] = board->knightBlack->symbol;
    (board->boardData)[7][2] = board->bishopBlack->symbol;(board->boardData)[7][5] = board->bishopBlack->symbol;
    (board->boardData)[7][3] = board->queenBlack->symbol;(board->boardData)[7][4] = board->kingBlack->symbol;
    
}

void _init_pieces(chessBoard* board, int mode) {
    board->kingBlack = init_king(mode, BLACKCOLOR);
    board->pawnBlack = init_pawn(mode, BLACKCOLOR);
    board->rookBlack = init_rook(mode, BLACKCOLOR);
    board->queenBlack = init_queen(mode, BLACKCOLOR);
    board->bishopBlack = init_bishop(mode, BLACKCOLOR);
    board->knightBlack = init_knight(mode, BLACKCOLOR);
    
    board->kingWhite = init_king(mode, WHITECOLOR);
    board->pawnWhite = init_pawn(mode, WHITECOLOR);
    board->rookWhite = init_rook(mode, WHITECOLOR);
    board->queenWhite = init_queen(mode, WHITECOLOR);
    board->bishopWhite = init_bishop(mode, WHITECOLOR);
    board->knightWhite = init_knight(mode, WHITECOLOR);

}

chessBoard* init_game_board(int mode) {
    
    // MEM:
    
    chessBoard* board = (chessBoard *) malloc(sizeof(chessBoard));
    
    // INIT:
    
    _init_pieces(board, mode);
    _init_board_data(board);
    
    return board;
}
