//
//  ChessBoard.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#include "ChessBoard.h"
// TODO: Implement
void _init_board_data(ChessBoard* board) {
    
    // init NULL:
    
    for (int row = 0; row<BOARD_SIZE; row ++)
        for (int col = 0; col<BOARD_SIZE; col++)
            (board->boardData)[row][col] = NULL;
    
    
    // init pawns:
    for (int i = 0; i<BOARD_SIZE; i++) (board->boardData)[1][i] = board->pawnWhite;
    for (int i = 0; i<BOARD_SIZE; i++) (board->boardData)[6][i] = board->pawnBlack;
    
    // init others:
    (board->boardData)[0][0] = board->rookWhite;(board->boardData)[0][7] = board->rookWhite;
    (board->boardData)[0][1] = board->knightWhite;(board->boardData)[0][6] = board->knightWhite;
    (board->boardData)[0][2] = board->bishopWhite;(board->boardData)[0][5] = board->bishopWhite;
    (board->boardData)[0][3] = board->kingWhite;(board->boardData)[0][4] = board->queenWhite;
    
    (board->boardData)[7][0] = board->rookBlack;(board->boardData)[7][7] = board->rookBlack;
    (board->boardData)[7][1] = board->knightBlack;(board->boardData)[7][6] = board->knightBlack;
    (board->boardData)[7][2] = board->bishopBlack;(board->boardData)[7][5] = board->bishopBlack;
    (board->boardData)[7][3] = board->queenBlack;(board->boardData)[7][4] = board->kingBlack;
    
}

void _init_pieces(ChessBoard* board, int mode, SDL_Renderer* renderer) {
    board->kingBlack = init_king(mode, renderer, BLACKCOLOR);
    board->pawnBlack = init_pawn(mode, renderer, BLACKCOLOR);
    board->rookBlack = init_rook(mode, renderer, BLACKCOLOR);
    board->queenBlack = init_queen(mode, renderer, BLACKCOLOR);
    board->bishopBlack = init_bishop(mode, renderer, BLACKCOLOR);
    board->knightBlack = init_knight(mode, renderer, BLACKCOLOR);
    
    board->kingWhite = init_king(mode, renderer, WHITECOLOR);
    board->pawnWhite = init_pawn(mode, renderer, WHITECOLOR);
    board->rookWhite = init_rook(mode, renderer, WHITECOLOR);
    board->queenWhite = init_queen(mode, renderer, WHITECOLOR);
    board->bishopWhite = init_bishop(mode, renderer, WHITECOLOR);
    board->knightWhite = init_knight(mode, renderer, WHITECOLOR);

}
// renderer will be NULL if game mode is console
ChessBoard* init_game_board(int mode, SDL_Renderer* renderer) {
    
    // MEM:
    
    ChessBoard* board = (ChessBoard *) malloc(sizeof(GamePiece*) * sizeof(ChessBoard));
    
    // INIT:
    if (mode == GAME_MODE_WITH_GUI) {
        _init_pieces(board, mode, renderer);
        _init_board_data(board);
    }
    
    return board;
}
