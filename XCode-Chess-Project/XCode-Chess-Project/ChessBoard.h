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
#include "GameGraphicalPiece.h"
#include "SDLUtils.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#define BOARD_SIZE 8
#define NUMBER_OF_GAME_PIECE_TYPES 6
#define PLAYERS_COUNT 2
#define EMPTY_SLOT_CHAR '_'

typedef struct ChessBoard {
    GamePiece* boardData[BOARD_SIZE][BOARD_SIZE];
    
    //these are all the game pieces single instances,used for not re creating them when they are multiple(like pawns) , in practice not so heavy
    // the order is <blacks array>,<whites array> in each array the pieces are organized by the order of pieces types in PieceType enum
    //TODO:FOR LEON, think do we really need it> can't we just move pioeces using a position on board and just replaceing stuff, we will only recreate figures few times
    GamePiece* allGamePieces[PLAYERS_COUNT][NUMBER_OF_GAME_PIECE_TYPES];
   
    GamePiece* kingWhite;
    GamePiece* queenWhite;
    GamePiece* rookWhite;
    GamePiece* knightWhite;
    GamePiece* bishopWhite;
    GamePiece* pawnWhite;
    
    GamePiece* kingBlack;
    GamePiece* queenBlack;
    GamePiece* rookBlack;
    GamePiece* knightBlack;
    GamePiece* bishopBlack;
    GamePiece* pawnBlack;
    
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

#endif /* ChessBoard_h */
