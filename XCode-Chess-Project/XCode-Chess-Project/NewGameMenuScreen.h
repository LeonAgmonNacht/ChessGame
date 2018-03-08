//
//  NewGameMenuScreen.h
//  XCode-Chess-Project
//
//  Created by לאון אגמון נכט on 04/03/2018.
//  Copyright © 2018 LeonApps. All rights reserved.
//

#ifndef NewGameMenuScreen_h
#define NewGameMenuScreen_h
#include "ChessGame.h"
#include <stdio.h>

/**
 Holds the data for a Settings screen - a screen that allows the user to choose settings for the game
 */
typedef struct _settings_screen {
    SDL_Window *window;
    SDL_Renderer *windowRenderer;
} SettingsScreen;

SettingsScreen* init_settings_screen(void);
GameSettings* wait_for_start(SettingsScreen* screen);

#endif /* NewGameMenuScreen_h */
