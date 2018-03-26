//
//  ChessBoard.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#ifndef ChessBoard_h
#define ChessBoard_h


#include "GamePieces.h"
#include "SDLUtils.h"
#include <stdio.h>
#include "List.h"
#include <SDL.h>
#include <SDL_video.h>
#define NUMBER_OF_BOARD_ROWS 8
#define NUMBER_OF_BOARD_COLUMNS 8
#define NUMBER_OF_GAME_PIECE_TYPES 6
#define PLAYERS_COUNT 2
#define EMPTY_SLOT_CHAR '_'
#define PIECES_INDEX(isWhite) isWhite ? 1:0
/**
CHESS BOARD REPRESENTATION
 */
typedef struct ChessBoard {
    // representive of a game board
    GamePiece* boardData[NUMBER_OF_BOARD_ROWS][NUMBER_OF_BOARD_COLUMNS];
    
    //2d array of lists, where first index is 0 for black player 1 for white player and second array is the index according to game piece type(each index corresponds to the order in enum of pieces types)
    List* gamePieces[PLAYERS_COUNT][NUMBER_OF_GAME_PIECE_TYPES];
    
} ChessBoard;




/**
 get a piece single instance
 
 @param board board of game
 @param type the type of the piece
 @param isWhite boolean of is white
 @return the single instance piece on the board
 */
GamePiece* get_piece_with_type_and_color(ChessBoard* board, PieceType type,bool isWhite);
/**
 Inits a new game board
 */
ChessBoard* init_game_board();



void free_chess_board(ChessBoard* board);
/**
 Prints the given board to f
 */
void print_board_to_file(ChessBoard* board, FILE* f);

/**
 Preforms a move
 */
void preform_board_move(ChessBoard*board, Cell* startCell, Cell* destCell);

/**
 Copies the content of the from board data to the to
 */
//TODO: LEON DELETE
//void copy_board_data(GamePiece* from, GamePiece* to);
/**
 Loads a ChessBoard from the given (valid!) file.
 */
ChessBoard* load_board_from_file(FILE* file);

/**
 copy board
 
 @param board original board
 @return new board
 */
ChessBoard* copy_board(ChessBoard* board);


/**
 make a move on board
 
 @param board board
 @param pieceToMove the piece to move
 @param cellToMoveTo the cell to move to the piece
 */
void make_move_on_board(ChessBoard* board, GamePiece* pieceToMove,Cell* cellToMoveTo);
#endif /* ChessBoard_h */
