//
//  GamePieces.c
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 19/02/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#include "GamePieces.h"
#include <stdlib.h>
#include <unistd.h>

gamePiece* _init_game_piece(int mode, SDL_Renderer* renderer, int color, char symbol, char* imagePath) {
    gamePiece* piece = (gamePiece*) malloc(sizeof(gamePiece));
    piece->symbol = symbol;
    piece->color = color;
    
    if (mode == GAME_MODE_WITH_GUI) {
        // load an image onto an SDL surface
        SDL_Surface* surf = SDL_LoadBMP(imagePath);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
        piece->texture = tex;
        
    }
    return piece;
}

char _get_symbol_by_color(int color, char blackSymbol, char whiteSymbol) {
    if (color == BLACKCOLOR) return blackSymbol;
    else return whiteSymbol;
}

// NOTE: Image with a table of name-per-image can be found in the gui-resources folder.
// NOTE: Renderer will be NULL if game mode is console
// TODO: Add images paths


gamePiece* init_king(int mode, SDL_Renderer* renderer, int color) {
    char symbol = _get_symbol_by_color(color, 'K', 'k');
    return _init_game_piece(mode, renderer, color, symbol,
                            color == BLACKCOLOR ? "./GUI-Resources/Chess_kdt60.bmp":"./GUI-Resources/Chess_klt60.bmp");
}

gamePiece* init_queen(int mode, SDL_Renderer* renderer, int color) {
    char symbol = _get_symbol_by_color(color, 'Q', 'q');
    return _init_game_piece(mode, renderer, color, symbol,
                            color == BLACKCOLOR ? "./GUI-Resources/Chess_qdt60.bmp":"./GUI-Resources/Chess_qlt60.bmp");

}

gamePiece* init_rook(int mode, SDL_Renderer* renderer, int color) {
    char symbol = _get_symbol_by_color(color, 'R', 'r');
    return _init_game_piece(mode, renderer, color, symbol,
                            color == BLACKCOLOR ? "./GUI-Resources/Chess_rdt60.bmp":"./GUI-Resources/Chess_rlt60.bmp");

}

gamePiece* init_bishop(int mode, SDL_Renderer* renderer, int color) {
    char symbol = _get_symbol_by_color(color, 'B', 'b');
    return _init_game_piece(mode, renderer, color, symbol,
                            color == BLACKCOLOR ? "./GUI-Resources/Chess_bdt60.bmp":"./GUI-Resources/Chess_blt60.bmp");

}

gamePiece* init_knight(int mode, SDL_Renderer* renderer, int color) {
    char symbol = _get_symbol_by_color(color, 'N', 'n');
    return _init_game_piece(mode, renderer, color, symbol,
                            color == BLACKCOLOR ? "./GUI-Resources/Chess_ndt60.bmp":"./GUI-Resources/Chess_nlt60.bmp");

}

gamePiece* init_pawn(int mode, SDL_Renderer* renderer, int color) {
    char symbol = _get_symbol_by_color(color, 'M', 'm');
    return _init_game_piece(mode, renderer, color, symbol,
                            color == BLACKCOLOR ? "./GUI-Resources/Chess_pdt60.bmp":"./GUI-Resources/Chess_plt60.bmp");

}





