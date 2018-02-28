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
    GamePiece* boardData[BOARD_SIZE][BOARD_SIZE];
    
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
    
} chessBoard;

chessBoard* init_game_board(int mode, SDL_Renderer* renderer);

#endif /* ChessBoard_h */
