//
//  ChessBoard.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#include "ChessBoard.h"
#include "GamePieces.h"
#define WHITE_PAWNS_ROW_INDEX 1
#define BLACK_PAWNS_ROW_INDEX 6

//THE ARRAY OF THE PIECES AS ORDERED IN CHESS GAME IN THE FIRST ROW FROM THE SIDE OF THE PLAYER
#define FIRST_ROW_OF_PIECES {Rook,Knight,Bishop,King,Queen,Bishop,Knight,Rook}
/**
 fill the board empty spaces with null

 @param board the board to fill
 */
static void fill_board_data_with_null(ChessBoard *board) {
    for (int row = 0; row<BOARD_SIZE; row ++)
        for (int col = 0; col<BOARD_SIZE; col++)
            (board->boardData)[row][col] = NULL;
}
/**
 get a piece single instance
 
 @param board board of game
 @param type the type of the piece
 @param isWhite boolean of is white
 @return the single instance piece on the board
 */
GamePiece* get_piece_with_type_and_color(ChessBoard* board, PieceType type,bool isWhite){
    return board->allGamePieces[isWhite ? 1:0][type];
}

/**
 init pawns when board is created

 @param board the game board
 */
static void init_pawns(ChessBoard *board) {
    // to remove
//    for (int i = 0; i<BOARD_SIZE; i++) (board->boardData)[WHITE_PAWNS_ROW_INDEX][i] = board->pawnWhite;
//    for (int i = 0; i<BOARD_SIZE; i++) (board->boardData)[BLACK_PAWNS_ROW_INDEX][i] = board->pawnBlack;
    for (int i = 0; i<BOARD_SIZE; i++) (board->boardData)[WHITE_PAWNS_ROW_INDEX][i] = get_piece_with_type_and_color(board, Pawn, true);
    for (int i = 0; i<BOARD_SIZE; i++) (board->boardData)[BLACK_PAWNS_ROW_INDEX][i] = get_piece_with_type_and_color(board, Pawn, false);
}

/**
 init the not pawn pieces when board is created

 @param board the board of game

 */
static void init_not_pawn_pieces(ChessBoard *board) {
     static const PieceType piecesArray[] = FIRST_ROW_OF_PIECES;
    int white_player_first_row_index = 0;
    for(int i = 0;i<BOARD_SIZE;i++){
        board->boardData[white_player_first_row_index][i] = get_piece_with_type_and_color(board, piecesArray[i], true);
    }
    // a nick name for the row of pieces of black player(not the pawns one, the second one)
    int black_player_first_row_index = 0;
    for(int i = 0;i<BOARD_SIZE;i++){
        board->boardData[black_player_first_row_index][i] = get_piece_with_type_and_color(board, piecesArray[i], false);
    }
}

// TODO: Implement
void _init_board_data(ChessBoard* board) {
    
    // init NULL:
    
    fill_board_data_with_null(board);
//    // init pawns:
    init_pawns(board);
    // a nick name for the row of pieces of white player(not the pawns one, the second one)
    init_not_pawn_pieces(board);
// to remove
//    // init others:
//    (board->boardData)[0][0] = board->rookWhite;(board->boardData)[0][7] = board->rookWhite;
//    (board->boardData)[0][1] = board->knightWhite;(board->boardData)[0][6] = board->knightWhite;
//    (board->boardData)[0][2] = board->bishopWhite;(board->boardData)[0][5] = board->bishopWhite;
//    (board->boardData)[0][3] = board->kingWhite;(board->boardData)[0][4] = board->queenWhite;
//
//    (board->boardData)[7][0] = board->rookBlack;(board->boardData)[7][7] = board->rookBlack;
//    (board->boardData)[7][1] = board->knightBlack;(board->boardData)[7][6] = board->knightBlack;
//    (board->boardData)[7][2] = board->bishopBlack;(board->boardData)[7][5] = board->bishopBlack;
//    (board->boardData)[7][3] = board->queenBlack;(board->boardData)[7][4] = board->kingBlack;
    
}

void _init_pieces(ChessBoard* board) {
    //to remove
//    board->kingBlack = init_king(mode, renderer, BLACKCOLOR);
//    board->pawnBlack = init_pawn(mode, renderer, BLACKCOLOR);
//    board->rookBlack = init_rook(mode, renderer, BLACKCOLOR);
//    board->queenBlack = init_queen(mode, renderer, BLACKCOLOR);
//    board->bishopBlack = init_bishop(mode, renderer, BLACKCOLOR);
//    board->knightBlack = init_knight(mode, renderer, BLACKCOLOR);
//
//    board->kingWhite = init_king(mode, renderer, WHITECOLOR);
//    board->pawnWhite = init_pawn(mode, renderer, WHITECOLOR);
//    board->rookWhite = init_rook(mode, renderer, WHITECOLOR);
//    board->queenWhite = init_queen(mode, renderer, WHITECOLOR);
//    board->bishopWhite = init_bishop(mode, renderer, WHITECOLOR);
//    board->knightWhite = init_knight(mode, renderer, WHITECOLOR);
    for(int i =0;i<PLAYERS_COUNT;i++){
        for(int j=King;j<=Pawn;j++){
            board->allGamePieces[i][j]=init_game_piece(j, i == 0 ? false:true);
        }
    }
}



// renderer will be NULL if game mode is console
ChessBoard* init_game_board(int mode, SDL_Renderer* renderer) {
    
    // MEM:
    
    ChessBoard* board = (ChessBoard *) malloc(sizeof(GamePiece*) * sizeof(ChessBoard));
    _init_pieces(board);
    _init_board_data(board);
    // INIT:
//    if (mode == GAME_MODE_WITH_GUI) {
//        _init_pieces(board, mode, renderer);
//        _init_board_data(board);
//    }
    
    return board;
}
