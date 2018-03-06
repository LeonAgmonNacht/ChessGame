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


typedef struct Cell {
    int row;
    int column;
}Cell;


/**
 get posibble *legal* moves for player
 @param pieceOnBoardToCheck the piece on board we want to check the possible moves for
 @param board the current board of the game
 @return legal moves in a list,please notice that a move would be a Cell
 */
List* get_posibble_moves(Cell pieceOnBoardToCheck,ChessBoard* board);

#endif /* ChessGameMovesValidator_h */
