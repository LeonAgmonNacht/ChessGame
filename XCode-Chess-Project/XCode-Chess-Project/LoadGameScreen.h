//
//  LoadGameScreen.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 06/03/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#ifndef LoadGameScreen_h
#define LoadGameScreen_h

#include <stdio.h>
#include "ChessGame.h"
typedef struct _load_game_screen {
    SDL_Window *window;
    SDL_Renderer *windowRenderer;
} LoadGameScreen;

LoadGameScreen* init_load_game_screen();
ChessGame* wait_for_game(LoadGameScreen* screen);
void free_load_game_screen(LoadGameScreen* screen);

#endif /* LoadGameScreen_h */
