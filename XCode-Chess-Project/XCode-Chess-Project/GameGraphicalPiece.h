//
//  GameGraphicalPiece.h
//  XCode-Chess-Project
//
//  Created by daniel meltzer on 01/03/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#ifndef GameGraphicalPiece_h
#define GameGraphicalPiece_h
#include <SDL.h>
#include <SDL_video.h>
#include <stdio.h>
#include "GamePieces.h"
typedef struct GameGraphicalPiece {
    
    
    SDL_Texture * texture; // Will be NULL for console mode games
    GamePiece* gamePiece;
    
    
} GameGraphicalPiece;
#endif /* GameGraphicalPiece_h */
