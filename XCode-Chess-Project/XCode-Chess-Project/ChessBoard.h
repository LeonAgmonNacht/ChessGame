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
#include "SDLUtils.h"
#define BOARD_SIZE 8
#define EMPTY_SLOT_CHAR '_'

typedef struct _chess_board {
    char boardData[BOARD_SIZE][BOARD_SIZE];
    
    gamePiece* kingWhite;
    gamePiece* queenWhite;
    gamePiece* rookWhite;
    gamePiece* knightWhite;
    gamePiece* bishopWhite;
    gamePiece* pawnWhite;
    
    gamePiece* kingBlack;
    gamePiece* queenBlack;
    gamePiece* rookBlack;
    gamePiece* knightBlack;
    gamePiece* bishopBlack;
    gamePiece* pawnBlack;
    
} chessBoard;

chessBoard* init_game_board(int mode);

#endif /* ChessBoard_h */
