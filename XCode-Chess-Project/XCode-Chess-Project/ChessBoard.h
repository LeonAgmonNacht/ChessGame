//
//  ChessBoard.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#ifndef ChessBoard_h
#define ChessBoard_h

#include <stdio.h>
#include "GamePieces.h"

#define BOARD_SIZE 8
#define EMPTY_SLOT_CHAR '_'

typedef struct _chess_board {
    char* boardData;
    gamePiece* king;
    gamePiece* queen;
    gamePiece* rook;
    gamePiece* knight;
    gamePiece* bishop;
    gamePiece* pawn;
    
} chessBoard;

chessBoard* init_game_board();

#endif /* ChessBoard_h */
