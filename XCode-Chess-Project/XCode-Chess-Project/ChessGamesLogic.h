//
//  ChessGameMovesValidator.h
//  XCode-Chess-Project
//
//  Created by daniel meltzer on 28/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#ifndef ChessGameMovesValidator_h
#define ChessGameMovesValidator_h

#include <stdio.h>
#include "List.h"
#include "GamePieces.h"
#include "ChessBoard.h"
#include "Move.h"

typedef enum IsValidCases{
    IlegalMove,
    CheckAndCheckAfterwards,
    NewCheck,
    ValidMove
}IsValidCases;
/**
 get posibble *legal* moves for player
 @param pieceOnBoardToCheck the piece on board we want to check the possible moves for
 @param board the current board of the game
 @return legal moves in a list,please notice that a move would be a Move struct
 */
List* get_posibble_moves(Cell* pieceOnBoardToCheck, ChessBoard* board);


/**
 check if check accourd against player
 
 @param board the current board
 @param isWhite the player to check for: true means check for white player
 @return check if in the current board the player requested is under check
 */
bool is_check(ChessBoard* board , bool isWhite);

/**
 check if there is tie when next player to move is the white one
 
 @param board board to check the tie in
 @param isWhite the player that should move
 @return true if the player we check for is tied, false otherwise
 */
bool is_tie(ChessBoard* board,bool isWhite);

List* get_all_possible_moves(ChessBoard* board,bool isWhite);

IsValidCases isValidMove(ChessBoard* board, DetailedMove* move);
/**
 check if the game is in match state
 
 @param board board to check the match in
 @param isWhite player indicator to check if the piece matched is white
 @return true if there is a match against the player false otherwise
 */
bool is_match(ChessBoard* board, bool isWhite);

bool there_are_possible_moves(ChessBoard* board,bool isWhite);
#endif /* ChessGameMovesValidator_h */
