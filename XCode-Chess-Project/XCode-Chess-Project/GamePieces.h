//
//  GamePieces.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#ifndef GamePieces_h
#define GamePieces_h

# define BLACKCOLOR 0
# define WHITECOLOR 1

typedef struct _game_piece {
    char symbol;
    SDL_Texture* texture; // Will be NULL for console mode games
    int color;
} gamePiece;

gamePiece* init_king(int mode, int color);
gamePiece* init_queen(int mode, int color);
gamePiece* init_rook(int mode, int color);
gamePiece* init_bishop(int mode, int color);
gamePiece* init_knight(int mode, int color);
gamePiece* init_pawn(int mode, int color);

#include <stdio.h>

#endif /* GamePieces_h */
