//
//  GamePieces.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#ifndef GamePieces_h
#define GamePieces_h
#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <stdbool.h>
#include "GameSettings.h"

typedef enum{
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn
}PieceType;


typedef struct GamePiece {
    
    PieceType typeOfGamePiece;
    SDL_Texture * texture; // Will be NULL for console mode games
    bool isWhite;
    int color;
    char symbol;
} GamePiece;

/**
 get a char type from a game piece as specified in requirements

 @param gamePiece specified game piece to get char for
 @return char mathching to the requirements
 */
char get_char_from_game_piece(GamePiece* gamePiece);


// TODO: to remove
GamePiece* init_king(int mode, SDL_Renderer* renderer, int color);
GamePiece* init_queen(int mode, SDL_Renderer* renderer, int color);
GamePiece* init_rook(int mode, SDL_Renderer* renderer, int color);
GamePiece* init_bishop(int mode, SDL_Renderer* renderer, int color);
GamePiece* init_knight(int mode, SDL_Renderer* renderer, int color);
GamePiece* init_pawn(int mode, SDL_Renderer* renderer, int color);

GamePiece* init_game_piece(PieceType pieceType, bool isWhite);

#endif /* GamePieces_h */
