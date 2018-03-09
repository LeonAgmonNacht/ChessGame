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

LoadGameScreen* init_load_game_screen(bool shouldLoad);

/**
 Waits for the user to chose a slot, returns the slot index. If the back button was clicked, returns -1;
 The boolean shouldLoad controls which image should be presented: if true a load from slot image will be presented,
 if it is false, a save to slot image will be presented.
 */
int wait_for_slot_choice(LoadGameScreen* screen, bool shouldLoad);

void free_load_game_screen(LoadGameScreen* screen);

#endif /* LoadGameScreen_h */
