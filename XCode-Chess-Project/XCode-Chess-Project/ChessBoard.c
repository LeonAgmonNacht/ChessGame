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

/**
 THE ARRAY OF THE PIECES AS ORDERED IN CHESS GAME IN THE FIRST ROW FROM THE SIDE OF THE PLAYER
 */
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
    int black_player_first_row_index = 7;
    for(int i = 0;i<BOARD_SIZE;i++){
        board->boardData[black_player_first_row_index][i] = get_piece_with_type_and_color(board, piecesArray[i], false);
    }
}

// TODO: Implement
void _init_board_data(ChessBoard* board) {
    
    // init NULL:
    
    fill_board_data_with_null(board);
    // init pawns:
    init_pawns(board);
    // a nick name for the row of pieces of white player(not the pawns one, the second one)
    init_not_pawn_pieces(board);
    
}


/**
 initalizng board pieces single isntances,

 @param board the board of the game
 */
void _init_pieces(ChessBoard* board) {

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
    
    return board;
}

char* _get_row_data_string(ChessBoard* board, int row) {
    char* data = (char*) malloc(BOARD_SIZE*2);
    for (int col = 0; col<BOARD_SIZE*2; col+=2) {
        data[col] = board->boardData[row][col/2] == NULL ? '_' : get_char_from_game_piece(board->boardData[row][col/2]);
        data[col+1] = ' ';
    }
    return data;
}

/**
 Prints the given board to f
 */
void print_board_to_file(ChessBoard* board, FILE* f) {
    for (int row = 0; row<BOARD_SIZE; row++) {
        char* rowData = _get_row_data_string(board, row);
        fprintf(f, "%d| %s|\n", (8-row), rowData);
        free(rowData);
                                                         
    }
    fprintf(f, "  -----------------\n");
    fprintf(f, "   A B C D E F G H\n");
}
