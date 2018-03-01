//
//  GameGraphicalPiece.h
//  XCode-Chess-Project
//
//  Created by daniel meltzer on 01/03/2018.
//  Copyright © 2018 Daniel Meltzer and Leon Agmon Nacht. All rights reserved.
//

#ifndef GameGraphicalPiece_h
#define GameGraphicalPiece_h
#include <SDL.h>
#include <SDL_video.h>
#include <stdio.h>
#include "GamePieces.h"

/**
 a game graphical piece, this is used in order to enable us to represent the pieces on a Graphical Board
 In GUI mode.
 */
typedef struct GameGraphicalPiece {
    
    //texture element of the piece
    SDL_Texture * texture; // Will be NULL for console mode games
    //the data matching to the piece used for the game
    GamePiece* gamePiece;
    
    
} GameGraphicalPiece;


/**
 intializing graphical game piece

 @param renderer and sdl renderer to use
 @param gamePiece the game piece and it's data that the grpahical piece represent
 @return a graphical game piece with the graphical elements and other data required
 */
GameGraphicalPiece* initalize_graphichal_game_piece(SDL_Renderer* renderer,GamePiece* gamePiece);

#endif /* GameGraphicalPiece_h */
