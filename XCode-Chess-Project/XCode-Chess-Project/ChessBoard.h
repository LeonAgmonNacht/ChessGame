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
#include <SDL.h>
#include <SDL_video.h>
#define NUMBER_OF_BOARD_ROWS 8
#define NUMBER_OF_BOARD_COLUMNS 8
#define NUMBER_OF_GAME_PIECE_TYPES 6
#define PLAYERS_COUNT 2
#define EMPTY_SLOT_CHAR '_'


/**
CHESS BOARD REPRESENTATION
 
 */
typedef struct ChessBoard {
    // representive of a game board
    GamePiece* boardData[NUMBER_OF_BOARD_ROWS][NUMBER_OF_BOARD_COLUMNS];
    
    //TODO: Meltzer delete all game pieces
    
    /**
     these are all the game pieces single instances,used for not re creating them when they are multiple(like pawns) , in practice not so heavy. the order is <blacks array>,<whites array> in each array the pieces are organized by the order of pieces types in PieceType enum
    */
    GamePiece* allGamePieces[PLAYERS_COUNT][NUMBER_OF_GAME_PIECE_TYPES];
    
} ChessBoard;
/**
 get a piece single instance
 
 @param board board of game
 @param type the type of the piece
 @param isWhite boolean of is white
 @return the single instance piece on the board
 */
GamePiece* get_piece_with_type_and_color(ChessBoard* board, PieceType type,bool isWhite);

ChessBoard* init_game_board(int mode, SDL_Renderer* renderer);

/**
 Prints the given board to f
 */
void print_board_to_file(ChessBoard* board, FILE* f);

#endif /* ChessBoard_h */
